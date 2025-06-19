#include "stat.h"
#include <stdio.h>
#include <string.h>
static int total_requests = 0;
void stat_increment(const char* ip, const char* uri) {
    total_requests++;
}
void stat_dump_json(int fd) {
    dprintf(fd, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"total_requests\":%d}", total_requests);
}