//
// Created by darekparodia on 9/13/24.
//

#include "connection_handler.h"
#include "data/updater.h"

namespace network
{
    server srv;
    std::vector<network::Connection *> connections;
    std::vector<network::message> messages;
    std::thread update_thread;
    bool stopThread = false;

    void addConnection(websocketpp::connection_hdl hdl)
    {
        // Add connection
        connections.push_back(new Connection(hdl));
        logger.debug("Adding connection, " + std::to_string(connections.size()) + " to connections");
    }

    void removeConnection(websocketpp::connection_hdl hdl)
    {
        // Remove connection
        for (int i = 0; i < connections.size(); i++)
        {
            if (!connections[i]->get_hdl().expired() && !hdl.expired() && connections[i]->get_hdl().lock() == hdl.lock())
            {
                connections.erase(connections.begin() + i);
                break;
            }
        }

        logger.debug("Removing connection, " + std::to_string(connections.size()) + " to connections");
    }

    network::Connection *findConnection(websocketpp::connection_hdl hdl)
    {
        // Find connection
        for (int i = 0; i < connections.size(); i++)
        {
            if (!connections[i]->get_hdl().expired() && !hdl.expired() && connections[i]->get_hdl().lock() == hdl.lock())
            {
                return connections[i];
            }
        }

        return nullptr;
    }

    void on_message(server *s, websocketpp::connection_hdl hdl, server::message_ptr msg)
    {
        // Handle message
        logger.log("Received message: " + msg->get_payload());
        network::Connection *conn = findConnection(hdl);
        if (conn != nullptr)
        {
            conn->send(msg->get_payload());
        }
    }

    void on_open(server *s, websocketpp::connection_hdl hdl)
    {
        // Handle open
        logger.log("Connection opened");
        addConnection(hdl);
        data::resendLastMessages();
    }

    void on_close(server *s, websocketpp::connection_hdl hdl)
    {
        // Handle close
        logger.log("Connection closed");
        removeConnection(hdl);
    }

    void server_setup()
    {
        // Setup server
        try
        {
            if (settings::debug)
            {
                srv.set_access_channels(websocketpp::log::alevel::all);
            }
            else
            {
                srv.set_access_channels(websocketpp::log::alevel::none);
            }
            srv.clear_access_channels(websocketpp::log::alevel::frame_payload);
            srv.init_asio();
            srv.set_message_handler(bind(&on_message, &srv, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
            srv.set_open_handler(bind(&on_open, &srv, websocketpp::lib::placeholders::_1));
            srv.set_close_handler(bind(&on_close, &srv, websocketpp::lib::placeholders::_1));
            srv.listen(settings::port);
            srv.set_reuse_addr(true);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void start_server()
    {
        // Start server
        try
        {
            srv.start_accept();
            srv.run();
            stopThread = false;
            update_thread = std::thread([]()
                                        {
                while (!stopThread){
                    logger.debug("Sending messages");
                    sendAll();
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                } });
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void stop_server()
    {
        // Stop server
        try
        {
            logger.debug("Stopping server");
            stopThread = true;
            update_thread.join();
            srv.stop();
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void addMessage(message msg)
    {
        messages.push_back(msg);
        logger.debug("Adding message to queue, " + std::to_string(messages.size()) + " in queue");
        sendAll();
    }

    std::string convertMessages()
    {
        nlohmann::json j;

        // copy messages vector
        std::vector<network::message> msg_copy = messages;
        messages.clear();

        for (int i = 0; i < msg_copy.size(); i++)
        {
            j.push_back(nlohmann::json{
                {"type", msg_copy[i].type},
                {"data", msg_copy[i].data}});
        }

        // convert to string
        return j.dump();
    }

    void sendAll()
    {
        if (messages.size() == 0 || connections.size() == 0)
        {
            return;
        }

        std::string msg = convertMessages();
        for (int i = 0; i < connections.size(); i++)
        {
            connections[i]->send(msg);
        }
    }

    bool canAcceptMessages()
    {
        return connections.size() > 0;
    }

}