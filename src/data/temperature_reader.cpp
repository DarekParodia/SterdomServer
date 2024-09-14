//
// Created by darekparodia on 9/14/24.
//

#include "readers.h"

namespace data
{
    TemperatureReader::TemperatureReader(std::string serverUrl)
    {
        this->serverUrl = serverUrl;
    }

    TemperatureReader::~TemperatureReader() = default;

    void TemperatureReader::update()
    {
        // Read temperature
        try
        {
            logger.info("updating temperature");
            std::string temperature;

            // download temperature using curl
            temperature = network::download(settings::temp_esp_url);

            if (network::getDownloadStatus() != network::download_status::SUCCESS)
            {
                logger.error("failed to download temperature");
                return;
            }

            if (temperature != this->temperature){
                this->temperature = temperature;
                network::message msg;
                msg.type = network::msg_type::TEMP;
                msg.data = this->temperature;
                this->messageCallback(msg);
                logger.info("added message: " + msg.data);
                this->lastMessage = msg;
            }
        }
        catch (const std::exception &e)
        {
            logger.error(e.what());
        }
    }
}
