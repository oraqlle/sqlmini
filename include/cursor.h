/** @brief ABC
 *
 * @file cursor.h
 */

#ifndef sqlmini_cursor_h
#define sqlmini_cursor_h

#include "pager.h"

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief ABC
 */
typedef struct {
    Table *table;
    uint64_t row_num;
    bool end_of_table;
} Cursor;

/**
 * @brief ABC
 */
Cursor *cursor_at_table_start(Table *table);

/**
 * @brief ABC
 */
Cursor *cursor_at_table_end(Table *table);

/**
 * @brief ABC
 */
void cursor_advance(Cursor *cursor);

#endif // sqlmini_cursor_h
