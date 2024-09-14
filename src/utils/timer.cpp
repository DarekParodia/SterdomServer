#include "timer.h"

timer program_timer;

timer::timer()
{
    reset();
    start();
}

void timer::start()
{
    start_time = std::chrono::high_resolution_clock::now();
}

void timer::reset()
{
    start_time = std::chrono::high_resolution_clock::now();
}

void timer::runInterval(uint interval, void (*callback)())
{
    double elapsed_time = elapsed();
    if (elapsed_time >= interval)
    {
        callback();
        reset();
    }
}

double timer::elapsed() const
{
    return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();
}

std::string timer::elapsed_str() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << elapsed();
    return oss.str();
}