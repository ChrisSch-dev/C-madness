#pragma once
#include "types.h"
int storage_create_table(const char* name, column_def_t* cols, int ncols);
int storage_insert_row(const char* table, const char** values, int nvals);
int storage_select_all(const char* table);
int storage_delete_where(const char* table, const char* col, const char* val);
int storage_update_where(const char* table, const char* col, const char* val, const char* target_col, const char* new_val);
int storage_drop_table(const char* table);
void storage_load_tables(table_meta_t* tables, int* ntables);
void storage_save_tables(table_meta_t* tables, int ntables);