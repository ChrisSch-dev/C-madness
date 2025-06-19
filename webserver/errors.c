#include "errors.h"
#include "config.h"
#include <stdio.h>
#include <unistd.h>
void send_error_page(int fd, int code) {
    // Try to open custom error_page, fallback to built-in
    FILE* f = fopen(server_conf.error_page, "r");
    if (!f) {
        dprintf(fd, "HTTP/1.1 %d Error\r\nContent-Type: text/html\r\n\r\n<h1>Error %d</h1>", code, code);
        return;
    }
    char buf[1024];
    dprintf(fd, "HTTP/1.1 %d Error\r\nContent-Type: text/html\r\n\r\n", code);
    while (fgets(buf, sizeof(buf), f)) write(fd, buf, strlen(buf));
    fclose(f);
}