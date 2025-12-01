#include "pager.h"
#include "table.h"

#include <stdint.h>
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
    table->num_rows = 0;

    for (uint64_t it = 0; it < TABLE_MAX_PAGES; it++) {
        if (table->pager->pages[it]) {
            free(table->pager->pages[it]);
        }
    }

    free(table);
}

byte_t *row_slot(Table *table, uint64_t row_num) {
    uint64_t page_num = row_num / ROWS_PER_PAGE;

    byte_t *page = get_page(table->pager, page_num);
    uint64_t row_offset = row_num % ROWS_PER_PAGE;
    uint64_t byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}
