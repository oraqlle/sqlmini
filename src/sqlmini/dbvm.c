#include "dbvm.h"

ExecuteResult execute_insert(Statement *stmt, Table *table) {
    printf("This is where we would do an insert.\n");
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *stmt, Table *table) {
    printf("This is where we would do an select.\n");
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *stmt, Table *table) {
    switch (stmt->type) {
        case STMT_INSERT:
            return execute_insert(stmt, table);
        case STMT_SELECT:
            printf("SELECT occurs\n");
            return execute_insert(stmt, table);
        default:
            return EXECUTE_ERROR;
    }
}
