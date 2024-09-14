//
// Created by darekparodia on 9/14/24.
//

#include "updater.h"

namespace data{
    std::thread updaterThread;
    std::vector<ReaderBase*> readers = {
        new TemperatureReader(settings::temp_esp_url)
    };
    bool updaterRunning = false;
    timer *tmr = new timer();

    void updateAll(){
        logger.info("update loop call");
        for(auto reader : readers){
            reader->update();
        }
    }

    void startUpdater(){
        logger.info("starting updater");
        tmr->start();
        updaterRunning = true;
        updaterThread = std::thread([](){
            while(updaterRunning){
                if (network::canAcceptMessages())
                tmr->runInterval(settings::reader_interval, updateAll);
            }
        });
    }

    void stopUpdater(){
        updaterRunning = false;
        if (updaterThread.joinable()){
            updaterThread.join();
        }
    }

    void resendLastMessages() {
        for(auto reader : readers){
            reader->resendLastMessage();
        }
    }


}
