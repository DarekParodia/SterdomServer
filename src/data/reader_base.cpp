//
// Created by darekparodia on 9/28/24.
//

#include "reader_base.h"

namespace data{
    void ReaderBase::addMessageCallback(void (*callback)(network::message msg)){
        this->messageCallback = callback;
    };

    network::message ReaderBase::getLastMessage() {
        return this->lastMessage;
    };

    void ReaderBase::resendLastMessage(){
        try {
            if (this->lastMessage.data.empty()){
                return;
            }
            this->messageCallback(this->lastMessage);
        } catch (std::exception &e) {
            logger.error(e.what());
        }
    };
}