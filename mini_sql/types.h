#pragma once
#define MAX_COLS 8
#define MAX_NAME 32

typedef enum { TYPE_INT, TYPE_TEXT } coltype_t;

typedef struct {
    char name[MAX_NAME];
    coltype_t type;
} column_def_t;

typedef struct {
    char name[MAX_NAME];
    int ncols;
    column_def_t cols[MAX_COLS];
} table_meta_t;