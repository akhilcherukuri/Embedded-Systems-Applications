#include "symbol_table.h"

static symbol_table_s symbol_table[1] = {{
    {"test_var", (void *)0x4000ffff},
}};

const size_t symbol_table__size __attribute__((used)) = 1;
const symbol_table_s *symbol_table__base __attribute__((used)) = symbol_table;
