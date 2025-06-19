#pragma once
typedef struct sql_stmt sql_stmt_t;
sql_stmt_t* parse_sql(const char* sql);
int exec_sql(sql_stmt_t* stmt);
void free_sql_stmt(sql_stmt_t* stmt);