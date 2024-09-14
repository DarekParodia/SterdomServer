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
            inline void addMessageCallback(void (*callback)(network::message)){
                this->messageCallback = callback;
            };
            inline network::message getLastMessage() {
                return this->lastMessage;
            };
            inline void resendLastMessage(){
                try {
                    if (this->lastMessage.data.empty()){
                        return;
                    }
                    this->messageCallback(this->lastMessage);
                } catch (std::exception &e) {
                    logger.error(e.what());
                }
            };
           protected:
            void (*messageCallback)(network::message) = &network::addMessage;
            network::message lastMessage;
    };
}

#endif //READER_BASE_H
