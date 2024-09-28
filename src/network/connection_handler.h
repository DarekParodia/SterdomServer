//
// Created by darekparodia on 9/13/24.
//

#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include <vector>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <mutex>
#include <thread>
#include "settings.h"
#include "connection.h"
#include "utils/logger.h"

typedef websocketpp::server<websocketpp::config::asio> server;

namespace network{
    extern server srv;

    enum msg_type {
        TEMP = 0
    };

    struct message {
        msg_type type;
        std::string data;
    };
    typedef struct message message;
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
    void addMessage(message msg);
    void sendAll();
    void parseMutex();
    bool canAcceptMessages();
    bool canSendMessages();
}

#endif //CONNECTION_HANDLER_H
