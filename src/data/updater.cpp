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

    std::mutex update_mutex;
    std::condition_variable update_cv;
    bool updaterPaused = true;

    void updateAll(){
        logger.info("update loop call");
        for(auto reader : readers){
            reader->update();
        }
    }

    void updater_thread(){
        while(updaterRunning){
            if (updaterPaused){
                std::unique_lock<std::mutex> lock(update_mutex);
                update_cv.wait(lock, [] { return !updaterPaused; });
            }

            if (network::canAcceptMessages())
                tmr->runInterval(settings::reader_interval, updateAll);
        }
    }

    void startUpdater(){
        logger.info("starting updater");
        tmr->start();
        updaterRunning = true;
        updaterThread = std::thread(updater_thread);
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

    void unpauseUpdater(){
        if (!updaterPaused) return;
        std::lock_guard<std::mutex> lock(update_mutex);
        updaterPaused = false;
        update_cv.notify_all();
    }

    void pauseUpdater(){
        updaterPaused = true;
    }



}
