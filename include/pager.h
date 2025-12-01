/** @brief ABC
 *
 * @file pager.h
 */

#ifndef sqlmini_pager_h
#define sqlmini_pager_h

#include <stdint.h>
#include <stdio.h>

#define TABLE_MAX_PAGES 100

typedef unsigned char byte_t;

typedef struct Table Table;

typedef struct {
    uint64_t file_len;
    FILE *file;
    byte_t *pages[TABLE_MAX_PAGES];
} Pager;

Pager *pager_open(const char *filename);

void pager_flush(Pager *pager, uint64_t page_num, uint64_t page_size);

byte_t *get_page(Pager *pager, uint64_t page_num);

#endif // sqlmini_pager_h
