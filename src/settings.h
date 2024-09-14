#pragma once

#include <string>
#include <cstdint>

// look for comments in .cpp file
namespace settings
{
    extern std::string program_name;
    extern std::string temp_esp_url;
    extern uint16_t port;
    extern uint reader_interval;
    extern bool verbose;
    extern bool debug;
    extern bool no_confirm;
}
