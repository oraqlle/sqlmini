#include "compiler.h"
#include "input.h"

#include <string.h>

PrepareResult prepare_statement(InputBuffer *inbuf, Statement *stmt) {
    if (strncmp(inbuf->buf, "insert", 6) == 0) {
        stmt->type = STMT_INSERT;
        return PREPARE_SUCCESS;
    }

    if (strcmp(inbuf->buf, "select") == 0) {
        stmt->type = STMT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNISED_STATEMENT;
}
