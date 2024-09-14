//
// Created by darekparodia on 9/14/24.
//

#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <string>
#include <curl/curl.h>
#include "utils/logger.h"

namespace network{
    enum download_status{
        SUCCESS,
        FAILED,
        IN_PROGRESS,
    };

    extern download_status status;

    std::string download(std::string url);
    void initCurl();
    inline download_status getDownloadStatus() {
        return status;
    };
}

#endif //DOWNLOAD_H
