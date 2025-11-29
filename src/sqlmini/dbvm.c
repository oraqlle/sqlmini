#include "dbvm.h"

void execute_statement(Statement *stmt) {
    switch (stmt->type) {
        case STMT_INSERT:
            printf("INSERT occurs\n");
            break;
        case STMT_SELECT:
            printf("SELECT occurs\n");
            break;
    }
}

