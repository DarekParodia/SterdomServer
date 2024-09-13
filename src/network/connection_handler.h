//
// Created by darekparodia on 9/13/24.
//

#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "settings.h"
#include "connection.h"
#include "utils/logger.h"

typedef websocketpp::server<websocketpp::config::asio> server;

namespace network{
    extern server srv;
/**
*
* @brief Setup server
*
* This function sets up the server with the necessary configurations.
*
* @return void
*/
    void server_setup();
    void start_server();
    void stop_server();
}

#endif //CONNECTION_HANDLER_H
