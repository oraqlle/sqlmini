#include "compiler.h"

#include <stdio.h>
#include <string.h>

PrepareResult prepare_statement(InputBuffer *inbuf, Statement *stmt) {
    if (strncmp(inbuf->buf, "insert", 6) == 0) {
        stmt->type = STMT_INSERT;

        int args_assigned =
            sscanf(inbuf->buf, "insert %u %s %s", &stmt->row_to_insert.id,
                   stmt->row_to_insert.username, stmt->row_to_insert.email);

        if (args_assigned < 3) {
            return PREPARE_SYNTAX_ERROR;
        }
        return PREPARE_SUCCESS;
    }

    if (strcmp(inbuf->buf, "select") == 0) {
        stmt->type = STMT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNISED_STATEMENT;
}
