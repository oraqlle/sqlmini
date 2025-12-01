#include "table.h"
#include "pager.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Table *db_open(const char *filename) {
    Pager *pager = pager_open(filename);
    uint64_t num_rows = pager->file_len / ROW_SIZE;

    Table *table = (Table *)malloc(sizeof(Table));
    table->pager = pager;
    table->num_rows = num_rows;

    return table;
}

void db_close(Table *table) {
    Pager *pager = table->pager;
    uint64_t num_full_pages = table->num_rows / ROWS_PER_PAGE;

    for (uint64_t it = 0; it < num_full_pages; it++) {
        if (pager->pages[it] == NULL) {
            continue;
        }

        pager_flush(pager, it, PAGE_SIZE);
        free(pager->pages[it]);
        pager->pages[it] = NULL;
    }

    uint64_t num_additional_rows = table->num_rows % ROWS_PER_PAGE;

    if (num_additional_rows > 0) {
        uint64_t page_num = num_full_pages;

        if (pager->pages[page_num] != NULL) {
            pager_flush(pager, page_num, num_additional_rows * ROW_SIZE);
            free(pager->pages[page_num]);
            pager->pages[page_num] = NULL;
        }
    }

    if (fclose(pager->file) == EOF) {
        printf("Error closing db file.\n");
        exit(EXIT_FAILURE);
    }

    for (uint64_t it = 0; it < TABLE_MAX_PAGES; it++) {
        byte_t *page = pager->pages[it];

        if (page != NULL) {
            free(page);
            pager->pages[it] = NULL;
        }
    }

    free(pager);
    free(table);
}

void pager_flush(Pager *pager, uint64_t page_num, uint64_t page_size) {
    if (pager->pages[page_num] == NULL) {
        printf("Tried to flush null page\n");
        exit(EXIT_FAILURE);
    }

    if (fseek(pager->file, page_num * PAGE_SIZE, SEEK_SET) != 0) {
        perror("page flush :: file seeking failed");
        exit(EXIT_FAILURE);
    }

    size_t bytes_written =
        fwrite(pager->pages[page_num], sizeof(byte_t), page_size, pager->file);

    if (bytes_written != page_size) {
        if (feof(pager->file)) {
            printf("page flush :: Error writing page\n");
        } else if (ferror(pager->file)) {
            perror("page flush :: Error writing page");
        }

        fclose(pager->file);
        exit(EXIT_FAILURE);
    }
}

byte_t *row_slot(Table *table, uint64_t row_num) {
    uint64_t page_num = row_num / ROWS_PER_PAGE;

    byte_t *page = get_page(table->pager, page_num);
    uint64_t row_offset = row_num % ROWS_PER_PAGE;
    uint64_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}
