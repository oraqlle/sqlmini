#include "dbvm.h"
#include "cursor.h"
#include "serialize.h"
#include "table.h"
#include <stdint.h>
#include <stdlib.h>

ExecuteResult execute_insert(Statement *stmt, Table *table) {
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_insert = &stmt->row_to_insert;
    Cursor *cursor = cursor_at_table_end(table);
    serialize_row(row_to_insert, cursor_value(cursor));
    table->num_rows += 1;

    free(cursor);

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *stmt, Table *table) {
    Row row = {0, "\0", "\0"};
    Cursor *cursor = cursor_at_table_end(table);

    while (!cursor->end_of_table) {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }

    free(cursor);

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
