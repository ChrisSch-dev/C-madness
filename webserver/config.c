#include "config.h"
#include <stdio.h>
#include <string.h>

server_conf_t server_conf;

bool config_load(const char* filename) {
    // Minimal INI-style parser as a stub
    FILE* f = fopen(filename, "r");
    if (!f) return false;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "listen_port = %d", &server_conf.listen_port) == 1) continue;
        if (sscanf(line, "listen_ip = %63s", server_conf.listen_ip) == 1) continue;
        if (sscanf(line, "logfile = %255s", server_conf.logfile) == 1) continue;
        if (sscanf(line, "error_page = %255s", server_conf.error_page) == 1) continue;
        // Add more as needed...
    }
    fclose(f);
    return true;
}