/** @brief ABC
 *
 * @file types.h
 */

#ifndef sqlmini_types_h
#define sqlmini_types_h

#include "input.h"

#include <stdint.h>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

/**
 * @brief ABC
 */
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

/**
 * @brief ABC
 */
typedef enum {
    STMT_INSERT,
    STMT_SELECT,
} StatementType;

/**
 * @brief ABC
 */
typedef struct {
    StatementType type;
    Row row_to_insert;
} Statement;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

static const uint32_t ID_SIZE = size_of_attribute(Row, id);
static const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
static const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
static const uint32_t ID_OFFSET = 0;
static const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
static const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
static const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

/**
 * @brief ABC
 */
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNISED_STATEMENT,
} PrepareResult;

/**
 * @brief ABC
 */
PrepareResult prepare_statement(InputBuffer *inbuf, Statement *stmt);

#endif // sqlmini_types_h
