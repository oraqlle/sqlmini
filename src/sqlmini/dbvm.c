#include "dbvm.h"
#include "serialize.h"
#include "table.h"
#include <stdint.h>

ExecuteResult execute_insert(Statement *stmt, Table *table) {
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_insert = &stmt->row_to_insert;
    byte_t *slot = row_slot(table, table->num_rows);
    serialize_row(row_to_insert, slot);
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *stmt, Table *table) {
    Row row = {0, "\0", "\0"};
    byte_t *slot = NULL;

    for (uint32_t it = 0; it < table->num_rows; it++) {
        slot = row_slot(table, it);
        deserialize_row(slot, &row);
        print_row(&row);
    }

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *stmt, Table *table) {
    switch (stmt->type) {
        case STMT_INSERT:
            return execute_insert(stmt, table);
        case STMT_SELECT:
            return execute_select(stmt, table);
        default:
            return EXECUTE_ERROR;
    }
}
