#include "compiler.h"
#include "table.h"

#include <stdlib.h>
#include <string.h>

PrepareResult prepare_insert(InputBuffer *inbuf, Statement *stmt) {
    if (strncmp(inbuf->buf, "insert", 6) == 0) {
        stmt->type = STMT_INSERT;

        char *keyword = strtok(inbuf->buf, " ");
        char *id_str = strtok(NULL, " ");
        char *uname = strtok(NULL, " ");
        char *email = strtok(NULL, " ");

        if (id_str == NULL || uname == NULL || email == NULL) {
            return PREPARE_SYNTAX_ERROR;
        }

        if (id_str[0] == '-') {
            return PREPARE_NEGATIVE_ID;
        }

        uint32_t id = (uint32_t)strtoul(id_str, NULL, 10);

        if (strlen(uname) > COLUMN_USERNAME_SIZE) {
            return PREPARE_STRING_TOO_LONG;
        }

        if (strlen(email) > COLUMN_EMAIL_SIZE) {
            return PREPARE_STRING_TOO_LONG;
        }

        stmt->row_to_insert.id = id;
        strcpy(stmt->row_to_insert.username, uname);
        strcpy(stmt->row_to_insert.email, email);

        return PREPARE_SUCCESS;
    }

    if (strcmp(inbuf->buf, "select") == 0) {
        stmt->type = STMT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNISED_STATEMENT;
}

PrepareResult prepare_statement(InputBuffer *inbuf, Statement *stmt) {
    return prepare_insert(inbuf, stmt);
}
