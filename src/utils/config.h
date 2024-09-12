//
// Created by darekparodia on 9/12/24.
//

#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_PATH "/etc/sterdomserver"
#define CONFIG_FILE "server.conf"

#include <string>
#include <filesystem>
#include <fstream>

#include "logger.h"

class Config {
    public:
        Config();
        ~Config();
        void init();
        std::string get_config_path();
        std::string get_config_file();
        std::string get_config_full_path();
    private:
        std::filesystem::path config_path;
};

// Global config object
extern Config config;

#endif //CONFIG_H
