/** @brief ABC
 *
 * @file dbvm.h
 */

#ifndef sqlmini_dbvm_h
#define sqlmini_dbvm_h

#include "compiler.h"

/**
 * @brief ABC
 */
typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_ERROR,
} ExecuteResult;

/**
 * @brief ABC
 */
ExecuteResult execute_insert(Statement *stmt, Table *table);

/**
 * @brief ABC
 */
ExecuteResult execute_select(Statement *stmt, Table *table);

/**
 * @brief ABC
 */
ExecuteResult execute_statement(Statement *stmt, Table *table);

#endif // sqlmini_dbvm_h
