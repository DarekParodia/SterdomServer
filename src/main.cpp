#include <csignal>
#include <cstdlib>

#include "utils/config.h"
#include "utils/general.h"
#include "utils/logger.h"
#include "settings.h"
#include "network/connection_handler.h"

void sigint_handler(int sig) {
    logger.warning("Caught SIGINT, stopping server...");
    network::stop_server();
    exit(0);
}

int main(int argc, char **argv) {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = sigint_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, nullptr);
    sigaction(SIGTERM, &sigIntHandler, nullptr);

    settings::program_name = argv[0];
    logger.log("Starting Sterdom Server...");
    logger.debug(utils::cstring_arr_to_str(argv, argc));

    // init config file
    config.init();

    // setup server
    network::server_setup();

    // start server
    network::start_server();

    pause();
    return 0;
}
