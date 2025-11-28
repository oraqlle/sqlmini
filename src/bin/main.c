#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buf;
    size_t len;
    ssize_t inplen;
} InputBuffer;

InputBuffer *new_input_buffer() {
    InputBuffer *inbuf = (InputBuffer *)malloc(sizeof(InputBuffer));

    inbuf->buf = NULL;
    inbuf->len = 0;
    inbuf->inplen = 0;

    return inbuf;
}

typedef enum {
    META_EXIT_SUCCESS,
    META_EXIT_FAILURE,
    META_CMD_SUCCESS,
    META_CMD_UNRECOGNISED_COMMAND,
} MetaCmdResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNISED_STATEMENT,
} PrepareResult;

typedef enum {
    STMT_INSERT,
    STMT_SELECT,
} StatementType;

typedef struct {
    StatementType type;
} Statement;

void close_input_buffer(InputBuffer *inbuf) {
    free(inbuf->buf);
    free(inbuf);
}

static void print_prompt() { printf("db > "); }

static void read_input(InputBuffer *inbuf) {
    ssize_t bytes_read = getline(&inbuf->buf, &inbuf->len, stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    inbuf->inplen = bytes_read - 1;
    inbuf->buf[bytes_read - 1] = '\0';
}

MetaCmdResult do_meta_command(InputBuffer *inbuf) {
    if (strcmp(inbuf->buf, ".exit") == 0) {
        return META_EXIT_SUCCESS;
    }

    return META_CMD_UNRECOGNISED_COMMAND;
}

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

int main(int argc, char *argv[]) {
    InputBuffer *input_buffer = new_input_buffer();

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

        Statement stmt = {STMT_INSERT};
        switch (prepare_statement(input_buffer, &stmt)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNISED_STATEMENT:
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buf);
                continue;
        }

        execute_statement(&stmt);
        printf("Executed.\n");
    }

    return 0;
}
