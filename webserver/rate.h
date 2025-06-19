#pragma once
#include <stdbool.h>
bool rate_limit_check(const char* ip);
void rate_limit_cleanup();