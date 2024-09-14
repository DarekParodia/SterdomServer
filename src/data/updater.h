//
// Created by darekparodia on 9/14/24.
//

#ifndef UPDATER_H
#define UPDATER_H

#include <thread>
#include <vector>
#include "reader_base.h"
#include "readers.h"
#include "settings.h"
#include "utils/timer.h"
#include "network/connection_handler.h"

namespace data{
    void startUpdater();
    void stopUpdater();
    void resendLastMessages();
}

#endif //UPDATER_H
