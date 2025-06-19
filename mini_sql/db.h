#pragma once
#include "types.h"
void db_init();
void db_shutdown();
int db_create_table(const char* name, column_def_t* cols, int ncols);
int db_insert_row(const char* table, const char** values, int nvals);
int db_select_all(const char* table);
int db_delete_where(const char* table, const char* col, const char* val);
int db_update_where(const char* table, const char* col, const char* val, const char* target_col, const char* new_val);
int db_drop_table(const char* name);