#include "table.h"
#include "cursor.h"
#include "pager.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Table *db_open(const char *filename) {
    Pager *pager = pager_open(filename);
    size_t num_rows = pager->file_len / ROW_SIZE;

    Table *table = (Table *)malloc(sizeof(Table));
    table->pager = pager;
    table->num_rows = (uint32_t)num_rows;

    return table;
}

void db_close(Table *table) {
    Pager *pager = table->pager;
    uint32_t num_full_pages = table->num_rows / ROWS_PER_PAGE;

    for (uint32_t idx = 0; idx < num_full_pages; idx++) {
        if (pager->pages[idx] == NULL) {
            continue;
        }

        pager_flush(pager, idx, PAGE_SIZE);
        free(pager->pages[idx]);
        pager->pages[idx] = NULL;
    }

    uint32_t num_additional_rows = table->num_rows % ROWS_PER_PAGE;

    if (num_additional_rows > 0) {
        uint32_t page_num = num_full_pages;

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

    for (uint32_t it = 0; it < TABLE_MAX_PAGES; it++) {
        byte_t *page = pager->pages[it];

        if (page != NULL) {
            free(page);
            pager->pages[it] = NULL;
        }
    }

    free(pager);
    free(table);
}

byte_t *cursor_value(Cursor *cursor) {
    uint32_t row_num = cursor->row_num;
    uint32_t page_num = row_num / ROWS_PER_PAGE;

    byte_t *page = get_page(cursor->table->pager, page_num);
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}
