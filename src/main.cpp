#include <iostream>
#include <ranges>
#include <thread>
#include <type_traits>
#include <algorithm>

#include "simulation/simulation.h"
#include "utils/measurer.h"

// template <typename T>
// void caller(T&& t) {
//     static_assert(std::is_invocable_r_v<void, T>, "T must be invocable");
//     int i = 0;
//     while (i++ < 100000000) t();
// }

// void test() {
//     int x = 2;
//     int y = 4;
//     volatile int z = x + y;
// }
// int main() {
//     khustup::utils::Measurer measurer;

//     measurer.reset();
//     std::function ff([]() {
//         int x = 2;
//         int y = 4;
//         volatile int z = x + y;
//     });
//     caller(ff);
//     std::cout << measurer.getElapsedTimeInMicroseconds() << std::endl;

//     measurer.reset();
//     caller([]() {
//         // int x = 2;
//         // int y = 4;
//         // volatile int z = x + y;
//         test();
//     });
//     std::cout << measurer.getElapsedTimeInMicroseconds() << std::endl;

//     measurer.reset();
//     caller(test);
//     std::cout << measurer.getElapsedTimeInMicroseconds() << std::endl;
// }
int main() {
    int i =0;
    auto handler = [](const khustup::models::DrawUpdate& drawUpdate) {
        std::ranges::for_each(drawUpdate.getPoints(), [](const khustup::models::DrawPoint& drawPoint) {
            std::cout << drawPoint.getCoorodinate().x() << ":" << drawPoint.getCoorodinate().y() << std::endl;
        });
    };
    khustup::simulation::Simulation<decltype(handler)> simulation;

    //simulation.setDrowUpdateHandler(std::move(handler));

    simulation.start();
    return 0;
}