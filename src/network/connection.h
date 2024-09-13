//
// Created by darekparodia on 9/13/24.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>
#include "connection_handler.h"
#include "utils/logger.h"

namespace network{
    class Connection{
        public:
            Connection(websocketpp::connection_hdl hdl);
            ~Connection();
            void send(std::string message);
            inline websocketpp::connection_hdl get_hdl() {
                return this->hdl;
            };
        private:
            websocketpp::connection_hdl hdl;
    };
}

#endif //CONNECTION_H
