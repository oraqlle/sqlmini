#include "table.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Table *new_table(void) {
    Table *table = (Table *)malloc(sizeof(Table));
    table->num_rows = 0;

    for (uint32_t it = 0; it < TABLE_MAX_PAGES; it++) {
        table->pages[it] = NULL;
    }

    return table;
}

void free_table(Table *table) {
    table->num_rows = 0;

    for (uint32_t it = 0; it < TABLE_MAX_PAGES; it++) {
        if (table->pages[it]) {
            free(table->pages[it]);
        }
    }

    free(table);
}

byte_t *row_slot(Table *table, uint32_t row_num) {
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    byte_t *page = table->pages[page_num];

    if (page == NULL) {
        table->pages[page_num] = (byte_t *)calloc(PAGE_SIZE, 1);
        page = table->pages[page_num];
    }

    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}
