#pragma once
#include <stdbool.h>
bool auth_check(const char* auth_header, const char* realm);
void auth_send_challenge(int fd, const char* realm);