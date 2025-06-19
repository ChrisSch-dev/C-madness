#pragma once
#include "types.h"
typedef struct where_clause where_clause_t;
where_clause_t* parse_where(const char* expr);
int row_matches(const row_t* row, const where_clause_t* where);
void free_where(where_clause_t* where);