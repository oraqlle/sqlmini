/** @brief ABC
 *
 * @file compiler.h
 */

#ifndef sqlmini_compiler_h
#define sqlmini_compiler_h

#include "input.h"
#include "table.h"

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

#endif // sqlmini_compiler_h
