#include "cgi.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int cgi_handle(const char* path, int fd, const char* method, const char* query, const char* body) {
    int pid = fork();
    if (pid == 0) {
        // Set env vars, redirect fds, exec CGI script
        dup2(fd, 1);
        execl(path, path, NULL);
        exit(0);
    }
    waitpid(pid, NULL, 0);
    return 0;
}