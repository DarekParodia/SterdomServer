#pragma once

#include <string>
#include <cstdint>

// look for comments in .cpp file
namespace settings
{
    extern std::string program_name;
    extern uint16_t port;
    extern bool verbose;
    extern bool debug;
    extern bool no_confirm;
}
