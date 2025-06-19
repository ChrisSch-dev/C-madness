#pragma once
typedef struct order_by order_by_t;
order_by_t* parse_order_by(const char* expr);
void sort_rows(row_t* rows, int n, order_by_t* order);
void free_order_by(order_by_t* order);