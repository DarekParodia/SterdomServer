//
// Created by darekparodia on 9/14/24.
//

#include "download.h"

namespace network{
    CURL *curl;
    download_status status = download_status::SUCCESS;

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string download(std::string url){
        // download file from url
        // and call callback with downloaded data
        status = download_status::IN_PROGRESS;
        logger.info("downloading from: " + url);
        std::string data;

        if (!curl){
            initCurl();
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK){
            logger.error("curl failed: " + std::string(curl_easy_strerror(res)));
            status = download_status::FAILED;
            return "";
        }

        status = download_status::SUCCESS;

        return data;
    }

    void initCurl(){
        // initialize curl
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if (!curl){
            logger.error("curl init failed");
        }
    }
}