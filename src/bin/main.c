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

int main(int argc, char *argv[]) {
    InputBuffer *input_buffer = new_input_buffer();

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buf, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buf);
        }
    }

    return 0;
}
