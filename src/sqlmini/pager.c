#include "pager.h"
#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Pager *pager_open(const char *filename) {
    FILE *file = fopen(filename, "rb+");

    if (file == NULL) {
        // Create file if necessary
        printf("No file '%s' exists, creating in current directory\n", filename);
        file = fopen(filename, "wb+");

        if (file == NULL) {
            perror("Unable to create file");
            exit(EXIT_FAILURE);
        }
    }

    if (fseek(file, 0L, SEEK_END) != 0) {
        perror("opening pager :: file seeking failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    long len = ftell(file);

    if (len == -1L) {
        perror("opening pager :: could not obtain file position indicator");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    Pager *pager = (Pager *)malloc(sizeof(Pager));
    pager->file = file;
    pager->file_len = (uint64_t)len;

    for (uint64_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }

    if (fseek(file, 0L, SEEK_SET) != 0) {
        perror("opening pager :: file seeking failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    return pager;
}

byte_t *get_page(Pager *pager, uint64_t page_num) {
    if (page_num >= TABLE_MAX_PAGES) {
        printf("Tried to fetch page number out of bounds. %lu > %u\n", page_num,
               TABLE_MAX_PAGES);
        fclose(pager->file);
        exit(EXIT_FAILURE);
    }

    if (pager->pages[page_num] == NULL) {

        // Cache miss. Allocate memory and load from file
        byte_t *page = (byte_t *)calloc(PAGE_SIZE, sizeof(byte_t));
        uint64_t num_pages = pager->file_len / PAGE_SIZE;

        if (pager->file_len % PAGE_SIZE != 0) {
            num_pages += 1;
        }

        if (page_num < num_pages) {
            if (fseek(pager->file, page_num * PAGE_SIZE, SEEK_SET) != 0) {
                perror("loading page :: file seeking failed");
                fclose(pager->file);
                exit(EXIT_FAILURE);
            }

            size_t bytes_read =
                fread((void *)page, sizeof(byte_t), PAGE_SIZE, pager->file);

            if (bytes_read != PAGE_SIZE) {
                // Check bytes read for partial page
                if (bytes_read % ROW_SIZE != 0) {
                    if (ferror(pager->file)) { // errors
                        perror("reading page from file");
                    } else if (feof(pager->file)) {
                        printf("reading page from file :: unexpected EOF\n");
                    }

                    fclose(pager->file);
                    exit(EXIT_FAILURE);
                }
            }
        }

        pager->pages[page_num] = page;
    }

    return pager->pages[page_num];
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
        if (ferror(pager->file)) {
            perror("page flush :: Error writing page");
        }

        fclose(pager->file);
        exit(EXIT_FAILURE);
    }
}
