#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <pthread.h>

static FILE* logf = NULL;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void logger_init(const char* filename) {
    logf = fopen(filename, "a");
}
void logger_log(const char* ip, const char* path, int status) {
    pthread_mutex_lock(&mtx);
    if (logf) {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        fprintf(logf, "[%04d-%02d-%02d %02d:%02d:%02d] %s \"%s\" %d\n",
            t->tm_year+1900, t->tm_mon+1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec, ip, path, status);
        fflush(logf);
    }
    pthread_mutex_unlock(&mtx);
}
void logger_close() {
    if (logf) fclose(logf);
}