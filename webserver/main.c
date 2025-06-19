#include "server.h"
#include "logger.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <port> <web_root>\n", argv[0]);
        return 1;
    }
    int port = atoi(argv[1]);
    const char* root = argv[2];

    logger_init("server.log");
    mime_load_types("mime.types");
    server_start(port, root);
    logger_close();
    return 0;
}