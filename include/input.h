/** @brief ABC
 *
 * @file input.h
 */

#ifndef sqlmini_input_h
#define sqlmini_input_h

#include "table.h"

#include <stddef.h>
#include <stdio.h>

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
void read_input(InputBuffer *inbuf);

/**
 * @brief ABC
 */
void print_row(Row *row);

#endif // sqlmini_input_h
