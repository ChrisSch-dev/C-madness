#include "gz.h"
#include <zlib.h>
#include <string.h>
#include <unistd.h>
bool gz_send_compressed(int fd, const char* data, size_t len) {
    // Use zlib to compress and send data
    // Implementation omitted for brevity
    return true;
}