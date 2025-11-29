#include "input.h"

#include <stdlib.h>

InputBuffer *new_input_buffer(void) {
    InputBuffer *inbuf = (InputBuffer *)malloc(sizeof(InputBuffer));

    inbuf->buf = NULL;
    inbuf->len = 0;
    inbuf->input_len = 0;

    return inbuf;
}

void close_input_buffer(InputBuffer *inbuf) {
    free(inbuf->buf);
    free(inbuf);
}

ssize_t reads(char **restrict lineptr, size_t *restrict n, int delim, FILE *stream) {
    return -1;
}

void read_input(InputBuffer *inbuf) {
    ssize_t bytes_read = reads(&inbuf->buf, &inbuf->len, '\n', stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    inbuf->input_len = bytes_read - 1;
    inbuf->buf[bytes_read - 1] = '\0';
}

