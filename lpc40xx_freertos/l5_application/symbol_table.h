#pragma once

#include <stdlib.h>

typedef struct {
    const char *name[128U];
    const void *address;
} symbol_table_s;

extern const size_t symbol_table__size;
extern const symbol_table_s *symbol_table__base;
