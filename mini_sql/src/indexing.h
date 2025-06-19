#pragma once
int create_index(const char* table, const char* col);
int use_index(const char* table, const char* col, const value_t* v, int* row_ids, int* n);