#include "shutdown.h"
#include <signal.h>
volatile int server_running = 1;
static void sig_handler(int sig) {
    server_running = 0;
}
void setup_signal_handlers() {
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);
}