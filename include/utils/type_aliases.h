#pragma once

#include <chrono>
namespace khustup::utils {
    using Clock = std::chrono::steady_clock;
    using TimeStamp = std::chrono::time_point<std::chrono::steady_clock>;
    using Duration = std::chrono::milliseconds;
    using CoordinateType = uint16_t;
}