//
// Created by darekparodia on 9/14/24.
//

#ifndef READER_BASE_H
#define READER_BASE_H

#include "network/connection_handler.h"

namespace data{
    class ReaderBase{
        public:
            ReaderBase() = default;
            ~ReaderBase() = default;
            virtual void update() = 0;
            void addMessageCallback(void (*callback)(network::message msg));
            network::message getLastMessage();
            void resendLastMessage();
           protected:
            void (*messageCallback)(network::message) = &network::addMessage;
            network::message lastMessage;
    };
}

#endif //READER_BASE_H
