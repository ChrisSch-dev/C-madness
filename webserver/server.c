#include "server.h"
#include "http.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct {
    int client_fd;
    char root[256];
    struct sockaddr_in addr;
} client_info_t;

static void* thread_worker(void* arg) {
    client_info_t* ci = (client_info_t*)arg;
    char ip[32];
    inet_ntop(AF_INET, &ci->addr.sin_addr, ip, sizeof(ip));
    http_handle_request(ci->client_fd, ci->root, ip);
    close(ci->client_fd);
    free(ci);
    return NULL;
}

void server_start(int port, const char* root) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 64);
    printf("Serving %s on port %d\n", root, port);
    while (1) {
        client_info_t* ci = malloc(sizeof(client_info_t));
        socklen_t len = sizeof(ci->addr);
        ci->client_fd = accept(server_fd, (struct sockaddr*)&ci->addr, &len);
        strncpy(ci->root, root, sizeof(ci->root));
        pthread_t tid;
        pthread_create(&tid, NULL, thread_worker, ci);
        pthread_detach(tid);
    }
    close(server_fd);
}