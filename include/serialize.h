/** @brief ABC
 *
 * @file dbvm.h
 */

#ifndef sqlmini_serialize_h
#define sqlmini_serialize_h

#include "table.h"

/**
 * @brief ABC
 */
void serialize_row(Row *src, byte_t *dst);

/**
 * @brief ABC
 */
void derialize_row(byte_t *src, Row *dst);

#endif // sqlmini_dbvm_h
