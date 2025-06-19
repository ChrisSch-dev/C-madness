#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define META_FILE "meta.db"
#define DATA_EXT ".tbl"

void storage_load_tables(table_meta_t* tables, int* ntables) {
    *ntables = 0;
    FILE* f = fopen(META_FILE, "rb");
    if (!f) return;
    fread(ntables, sizeof(int), 1, f);
    fread(tables, sizeof(table_meta_t), *ntables, f);
    fclose(f);
}
void storage_save_tables(table_meta_t* tables, int ntables) {
    FILE* f = fopen(META_FILE, "wb");
    fwrite(&ntables, sizeof(int), 1, f);
    fwrite(tables, sizeof(table_meta_t), ntables, f);
    fclose(f);
}
int storage_create_table(const char* name, column_def_t* cols, int ncols) {
    char fname[128];
    snprintf(fname, sizeof(fname), "%s%s", name, DATA_EXT);
    FILE* f = fopen(fname, "wb");
    if (!f) return 1;
    fwrite(&ncols, sizeof(int), 1, f);
    fwrite(cols, sizeof(column_def_t), ncols, f);
    fclose(f);
    // Update meta
    FILE* fm = fopen(META_FILE, "ab");
    if (!fm) return 1;
    table_meta_t m;
    strcpy(m.name, name);
    m.ncols = ncols;
    memcpy(m.cols, cols, sizeof(column_def_t)*ncols);
    fwrite(&m, sizeof(table_meta_t), 1, fm);
    fclose(fm);
    return 0;
}
int storage_insert_row(const char* table, const char** values, int nvals) {
    char fname[128];
    snprintf(fname, sizeof(fname), "%s%s", table, DATA_EXT);
    FILE* f = fopen(fname, "ab");
    if (!f) return 1;
    for (int i=0;i<nvals;i++)
        fprintf(f, "%s\t", values[i]);
    fprintf(f, "\n");
    fclose(f);
    return 0;
}
int storage_select_all(const char* table) {
    char fname[128];
    snprintf(fname, sizeof(fname), "%s%s", table, DATA_EXT);
    FILE* f = fopen(fname, "r");
    if (!f) { printf("No such table.\n"); return 1; }
    char line[512];
    while (fgets(line, sizeof(line), f)) printf("%s", line);
    fclose(f);
    return 0;
}
int storage_delete_where(const char* table, const char* col, const char* val) {
    // Simple: not implemented for brevity
    printf("Delete not implemented yet.\n");
    return 1;
}
int storage_update_where(const char* table, const char* col, const char* val, const char* target_col, const char* new_val) {
    printf("Update not implemented yet.\n");
    return 1;
}
int storage_drop_table(const char* table) {
    char fname[128];
    snprintf(fname, sizeof(fname), "%s%s", table, DATA_EXT);
    remove(fname);
    printf("Table '%s' dropped.\n", table);
    return 0;
}