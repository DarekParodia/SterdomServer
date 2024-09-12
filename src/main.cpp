#include <iostream>
#include <websocketpp/server.hpp>

#include "utils/config.h"
#include "utils/general.h"
#include "utils/logger.h"
#include "settings.h"

int main(int argc, char **argv) {
    settings::program_name = argv[0];
    logger.log("Starting Sterdom Server...");
    logger.debug(utils::cstring_arr_to_str(argv, argc));

    // init config file
    config.init();
    return 0;
}
