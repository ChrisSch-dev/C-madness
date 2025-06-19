#pragma once
int join_tables(const char* left, const char* right, const char* on_clause, row_t** result, int* n_result);