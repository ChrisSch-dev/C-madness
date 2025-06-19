#include "rate.h"
#include <time.h>
#include <string.h>
#define RATE_LIMIT 100
#define TIME_WINDOW 60

typedef struct { char ip[64]; int count; time_t last_time; } rate_entry_t;
static rate_entry_t entries[1024];
static int n_entries = 0;

bool rate_limit_check(const char* ip) {
    time_t now = time(NULL);
    for (int i = 0; i < n_entries; ++i) {
        if (strcmp(entries[i].ip, ip) == 0) {
            if (now - entries[i].last_time > TIME_WINDOW) {
                entries[i].count = 1;
                entries[i].last_time = now;
                return true;
            }
            if (++entries[i].count > RATE_LIMIT)
                return false;
            return true;
        }
    }
    strcpy(entries[n_entries].ip, ip);
    entries[n_entries].count = 1;
    entries[n_entries].last_time = now;
    n_entries++;
    return true;
}
void rate_limit_cleanup() {
    // Omitted for brevity
}