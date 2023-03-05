#include "utils/measurer.h"

#include <chrono>

namespace khustup::utils {
Measurer::Measurer(bool paused) noexcept : _start_point(std::chrono::steady_clock::now()), _is_paused(paused) {}

void Measurer::pause() noexcept {
    _pause_point = std::chrono::steady_clock::now();
    _is_paused = true;
}

void Measurer::resume() noexcept {
    if (_is_paused) {
        _start_point += std::chrono::steady_clock::now() - _pause_point;
        _is_paused = false;
    }
}

void Measurer::reset() noexcept {
    _start_point = std::chrono::steady_clock::now();
    _is_paused = false;
}


[[nodiscard]] uint64_t Measurer::getElapsedTimeInSeconds() noexcept {
    return getElapsedTime<std::chrono::seconds>();
}

[[nodiscard]] uint64_t Measurer::getElapsedTimeInMilliseconds() noexcept {
    return getElapsedTime<std::chrono::milliseconds>();
}

[[nodiscard]] uint64_t Measurer::getElapsedTimeInMicroseconds() noexcept {

    return getElapsedTime<std::chrono::microseconds>();
}

} // namespace khustup::utils