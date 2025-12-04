/** @brief ABC
 *
 * @file table.h
 */

#ifndef sqlmini_table_h
#define sqlmini_table_h

#include "cursor.h"
#include "pager.h"

#include <stdint.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

/**
 * @brief ABC
 */
typedef struct {
    uint64_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

static const uint64_t ID_SIZE = size_of_attribute(Row, id);
static const uint64_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint64_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint64_t ID_OFFSET = 0;
static const uint64_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint64_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint64_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
static const uint64_t PAGE_SIZE = 4096;
static const uint64_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
static const uint64_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

struct Table {
    uint64_t num_rows;
    Pager *pager;
};

/**
 * @brief ABC
 */
Table *db_open(const char *filename);

/**
 * @brief ABC
 */
void db_close(Table *table);

/**
 * @brief ABC
 */
byte_t *cursor_value(Cursor *cursor);

#endif // sqlmini_table_h
