/** @brief ABC
 *
 * @file dbvm.h
 */

#ifndef sqlmini_serialize_h
#define sqlmini_serialize_h

#include "types.h"

/**
 * @brief ABC
 */
void serialize_row(Row *src, char *dst);

/**
 * @brief ABC
 */
void derialize_row(char *src, Row *dst);

#endif // sqlmini_dbvm_h
