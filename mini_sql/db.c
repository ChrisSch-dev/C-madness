#include "db.h"
#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 16
table_meta_t tables[MAX_TABLES];
int ntables = 0;

void db_init() {
    storage_load_tables(tables, &ntables);
}
void db_shutdown() {
    storage_save_tables(tables, ntables);
}
int db_create_table(const char* name, column_def_t* cols, int ncols) {
    if (storage_create_table(name, cols, ncols) == 0) {
        printf("Table '%s' created.\n", name);
        return 0;
    }
    printf("Error creating table.\n");
    return 1;
}
int db_insert_row(const char* table, const char** values, int nvals) {
    if (storage_insert_row(table, values, nvals) == 0) {
        printf("Inserted into '%s'.\n", table);
        return 0;
    }
    printf("Insert failed.\n");
    return 1;
}
int db_select_all(const char* table) {
    return storage_select_all(table);
}
int db_delete_where(const char* table, const char* col, const char* val) {
    return storage_delete_where(table, col, val);
}
int db_update_where(const char* table, const char* col, const char* val, const char* target_col, const char* new_val) {
    return storage_update_where(table, col, val, target_col, new_val);
}
int db_drop_table(const char* name) {
    return storage_drop_table(name);
}