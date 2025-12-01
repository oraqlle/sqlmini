#include "compiler.h"
#include "dbvm.h"
#include "input.h"
#include "table.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_prompt(void) { printf("db > "); }

typedef enum {
    META_EXIT_SUCCESS,
    META_EXIT_FAILURE,
    META_CMD_SUCCESS,
    META_CMD_UNRECOGNISED_COMMAND,
} MetaCmdResult;

MetaCmdResult do_meta_command(InputBuffer *inbuf) {
    if (strcmp(inbuf->buf, ".exit") == 0) {
        return META_EXIT_SUCCESS;
    }

    return META_CMD_UNRECOGNISED_COMMAND;
}

int main(int argc, char *argv[]) {
    InputBuffer *input_buffer = new_input_buffer();
    Table *table = new_table();

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buf[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case META_CMD_SUCCESS:
                    continue;
                case META_CMD_UNRECOGNISED_COMMAND:
                    printf("Unrecognized command '%s'.\n", input_buffer->buf);
                    continue;
                case META_EXIT_FAILURE:
                    exit(EXIT_FAILURE);
                    break;
                case META_EXIT_SUCCESS:
                    exit(EXIT_SUCCESS);
                    break;
            }
        }

        Statement stmt = {STMT_INSERT, {0, {0}, {0}}};
        switch (prepare_statement(input_buffer, &stmt)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_STRING_TOO_LONG:
                printf("String is too long.\n");
                continue;
            case PREPARE_SYNTAX_ERROR:
                printf("Syntax error. Could not parse statement.\n");
                break;
            case PREPARE_UNRECOGNISED_STATEMENT:
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buf);
                continue;
        }

        switch (execute_statement(&stmt, table)) {
            case EXECUTE_SUCCESS:
                printf("Executed.\n");
                break;
            case EXECUTE_TABLE_FULL:
                printf("Error: Table full.\n");
                break;
            case EXECUTE_ERROR:
                printf("Failed to execute.\n");
                break;
        }
    }

    close_input_buffer(input_buffer);
    free_table(table);

    return 0;
}
