/** @brief ABC
 *
 * @file input.h
 */

#ifndef sqlmini_input_h
#define sqlmini_input_h

#include <stddef.h>
#include <stdio.h>

typedef long long int ssize_t;

/**
 * @brief ABC
 */
typedef struct {
    char *buf;
    size_t len;
    ssize_t input_len;
} InputBuffer;

/**
 * @brief ABC
 */
InputBuffer *new_input_buffer(void);

/**
 * @brief ABC
 */
void close_input_buffer(InputBuffer *inbuf);

/**
 * @brief ABC
 */
ssize_t reads(char **restrict lineptr, size_t *restrict n, int delim, FILE *stream);

/**
 * @brief ABC
 */
void read_input(InputBuffer *inbuf);

#endif // sqlmini_input_h
