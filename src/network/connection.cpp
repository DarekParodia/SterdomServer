//
// Created by darekparodia on 9/13/24.
//

#include "connection.h"

namespace network
{
    Connection::Connection(websocketpp::connection_hdl hdl)
    {
        this->hdl = hdl;
    }

    Connection::~Connection() = default;

    void Connection::send(std::string message)
    {
        logger.debug("Sending message: " + message);
        // Send message
        try
        {
            network::srv.send(this->hdl, message, websocketpp::frame::opcode::text);
        }
        catch (const std::exception &e)
        {
            logger.error(e.what());
        }
    }
}
