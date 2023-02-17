#include <iostream>
#include <thread>

#include "utils/measurer.h"
int main() {
    khustup::utils::Measurer measurer;
    measurer.pause();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    measurer.resume();
    std::cout << "elapsed time in seconds      " << measurer.getElapsedTimeInSeconds() << std::endl;
    std::cout << "elapsed time in milliseconds " << measurer.getElapsedTimeInMilliseconds() << std::endl;
    std::cout << "elapsed time in microseconds " << measurer.getElapsedTimeInMicroseconds() << std::endl;
    return 0;
}