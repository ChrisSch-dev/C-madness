#include "db.h"
#include "parser.h"
#include "txn.h"
#include "net_server.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc > 1 && strcmp(argv[1], "--server") == 0) {
        return start_sql_server(atoi(argv[2]));
    }
    char cmd[1024];
    db_init();
    printf("MiniSQL Advanced. Type 'exit' to quit.\n");
    while (1) {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        if (!strncmp(cmd, "BEGIN", 5)) txn_begin();
        else if (!strncmp(cmd, "COMMIT", 6)) txn_commit();
        else if (!strncmp(cmd, "ROLLBACK", 8)) txn_rollback();
        else if (!strncmp(cmd, "exit", 4)) break;
        else exec_sql(parse_sql(cmd));
    }
    db_shutdown();
    return 0;
}