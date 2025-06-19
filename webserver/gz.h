#pragma once
#include <stdbool.h>
bool gz_send_compressed(int fd, const char* data, size_t len);