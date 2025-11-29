#include "input.h"

#include <stdio.h>
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

void read_input(InputBuffer *inbuf) {
    ssize_t bytes_read = getline(&inbuf->buf, &inbuf->len, stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    inbuf->input_len = bytes_read - 1;
    inbuf->buf[bytes_read - 1] = '\0';
}

