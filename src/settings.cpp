#include "settings.h"

// default settings
namespace settings
{
    std::string program_name = "filetovideo";
    std::string temp_esp_url = "http://192.168.1.208";
    uint16_t port = 33333;
    uint reader_interval = 2;
    bool verbose = true;
    bool debug = true;
    bool no_confirm = false;
}