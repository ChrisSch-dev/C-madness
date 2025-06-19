#include "parser.h"
#include "db.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void sql_parse_and_execute(const char* cmd) {
    if (!strncmp(cmd, "CREATE TABLE", 12)) {
        char tname[MAX_NAME], colsdef[256];
        sscanf(cmd, "CREATE TABLE %31s (%255[^)])", tname, colsdef);
        column_def_t cols[MAX_COLS];
        int ncols = 0;
        char* token = strtok(colsdef, ",");
        while (token && ncols < MAX_COLS) {
            char n[MAX_NAME], t[16];
            sscanf(token, " %31s %15s", n, t);
            strcpy(cols[ncols].name, n);
            cols[ncols].type = (strcasecmp(t,"INT")==0)?TYPE_INT:TYPE_TEXT;
            ncols++;
            token = strtok(NULL, ",");
        }
        db_create_table(tname, cols, ncols);
    } else if (!strncmp(cmd, "INSERT INTO", 11)) {
        char tname[MAX_NAME], vals[256];
        sscanf(cmd, "INSERT INTO %31s VALUES (%255[^)])", tname, vals);
        const char* values[MAX_COLS];
        int nvals = 0;
        char* token = strtok(vals, ",");
        while (token && nvals < MAX_COLS) {
            char* v = token; while (isspace(*v)) v++;
            values[nvals++] = v;
            token = strtok(NULL, ",");
        }
        db_insert_row(tname, values, nvals);
    } else if (!strncmp(cmd, "SELECT * FROM", 13)) {
        char tname[MAX_NAME];
        sscanf(cmd, "SELECT * FROM %31s", tname);
        db_select_all(tname);
    } else if (!strncmp(cmd, "DROP TABLE", 10)) {
        char tname[MAX_NAME];
        sscanf(cmd, "DROP TABLE %31s", tname);
        db_drop_table(tname);
    } else if (cmd[0] != '\n') {
        printf("Unknown or unsupported command.\n");
    }
}