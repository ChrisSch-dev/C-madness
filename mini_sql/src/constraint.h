#pragma once
int enforce_primary_key(const char* table, const row_t* row);
int enforce_unique(const char* table, const char* col, const char* value);