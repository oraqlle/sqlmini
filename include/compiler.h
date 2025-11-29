/** @brief ABC
 *
 * @file compiler.h
 */

#ifndef sqlmini_compiler_h
#define sqlmini_compiler_h

#include "input.h"

/**
 * @brief ABC
 */
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNISED_STATEMENT,
} PrepareResult;

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
} Statement;

/**
 * @brief ABC
 */
PrepareResult prepare_statement(InputBuffer *inbuf, Statement *stmt);

#endif // sqlmini_compiler_h
