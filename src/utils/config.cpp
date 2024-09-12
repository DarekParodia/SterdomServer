//
// Created by darekparodia on 9/12/24.
//

#include "config.h"

Config::Config() = default;

Config::~Config() = default;

void Config::init() {
    config_path = std::filesystem::path(CONFIG_PATH);

    // Check if config file exists
    if (!std::filesystem::exists(config_path / CONFIG_FILE)) {
        logger.warning("Config file does not exist, using default config. Create a config file at " + get_config_full_path() + " to change settings.");
    }
}


std::string Config::get_config_path() {
    return config_path.string();
}

std::string Config::get_config_file() {
    return CONFIG_FILE;
}

std::string Config::get_config_full_path() {
    return config_path.string() + "/" + CONFIG_FILE;
}

Config config;
