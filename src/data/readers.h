//
// Created by darekparodia on 9/14/24.
//

#ifndef READERS_H
#define READERS_H

#include "reader_base.h"
#include "utils/logger.h"
#include "network/download.h"
#include "settings.h"

namespace data {
    class TemperatureReader : public ReaderBase{
    public:
        TemperatureReader(std::string serverUrl);
        ~TemperatureReader();
        void update() override;
    private:
        std::string serverUrl;
        std::string temperature;
    };
}

#endif //READERS_H
