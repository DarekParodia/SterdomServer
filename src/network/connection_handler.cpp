//
// Created by darekparodia on 9/13/24.
//

#include "connection_handler.h"

namespace network{
    server srv;
    std::vector<network::Connection*> connections;

    void addConnection(websocketpp::connection_hdl hdl){
        // Add connection
        connections.push_back(new Connection(hdl));
        logger.debug("Adding connection, " + std::to_string(connections.size()) + " to connections");
    }

    void removeConnection(websocketpp::connection_hdl hdl){
        // Remove connection
        for (int i = 0; i < connections.size(); i++){
            if (!connections[i]->get_hdl().expired() && !hdl.expired() && connections[i]->get_hdl().lock() == hdl.lock()){
                connections.erase(connections.begin() + i);
                break;
            }
        }

        logger.debug("Removing connection, " + std::to_string(connections.size()) + " to connections");
    }

    network::Connection* findConnection(websocketpp::connection_hdl hdl){
        // Find connection
        for (int i = 0; i < connections.size(); i++){
            if (!connections[i]->get_hdl().expired() && !hdl.expired() && connections[i]->get_hdl().lock() == hdl.lock()){
                return connections[i];
            }
        }

        return nullptr;
    }

    void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg){
        // Handle message
        logger.log("Received message: " + msg->get_payload());
        network::Connection* conn = findConnection(hdl);
        if (conn != nullptr){
            conn->send(msg->get_payload());
        }

    }

    void on_open(server* s, websocketpp::connection_hdl hdl){
        // Handle open
        logger.log("Connection opened");
        addConnection(hdl);
    }

    void on_close(server* s, websocketpp::connection_hdl hdl){
        // Handle close
        logger.log("Connection closed");
        removeConnection(hdl);
    }

    void server_setup(){
        // Setup server
        try{
            srv.set_access_channels(websocketpp::log::alevel::all);
            srv.clear_access_channels(websocketpp::log::alevel::frame_payload);
            srv.init_asio();
            srv.set_message_handler(bind(&on_message, &srv, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
            srv.set_open_handler(bind(&on_open, &srv, websocketpp::lib::placeholders::_1));
            srv.set_close_handler(bind(&on_close, &srv, websocketpp::lib::placeholders::_1));
            srv.listen(settings::port);
        }catch (const std::exception &e){
            std::cout << e.what() << std::endl;
        }
    }

    void start_server(){
        // Start server
        try{
            srv.start_accept();
            srv.run();
        }catch (const std::exception &e){
            std::cout << e.what() << std::endl;
        }
    }

    void stop_server(){
        // Stop server
        try{
            srv.stop();
        }catch (const std::exception &e){
            std::cout << e.what() << std::endl;
        }
    }
}