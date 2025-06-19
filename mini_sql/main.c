#include "db.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>

int main() {
    char cmd[512];
    printf("MiniSQL Advanced. Type 'exit' to quit.\n");
    db_init();
    while (1) {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        if (!strncmp(cmd, "exit", 4)) break;
        sql_parse_and_execute(cmd);
    }
    db_shutdown();
    return 0;
}