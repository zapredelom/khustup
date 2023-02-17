#include <chrono>

namespace khustup::utils {
class Measurer {
public:
    Measurer(bool paused = false) noexcept;
    Measurer(const Measurer&) noexcept = delete;
    Measurer(Measurer&&) noexcept = delete;

    void pause() noexcept;
    void resume() noexcept;
    void reset() noexcept;

    [[nodiscard]] uint64_t getElapsedTimeInSeconds() noexcept;
    [[nodiscard]] uint64_t getElapsedTimeInMilliseconds() noexcept;
    [[nodiscard]] uint64_t getElapsedTimeInMicroseconds() noexcept;

    //~Measurer() noexcept;

private:
    template <typename Duration>
    [[nodiscard]] uint64_t getElapsedTime() noexcept;

private:
    std::chrono::time_point<std::chrono::steady_clock> _start_point;
    std::chrono::time_point<std::chrono::steady_clock> _pause_point;

    bool _is_paused;
};

template <typename Duration>
[[nodiscard]] uint64_t Measurer::getElapsedTime() noexcept {
    if (_is_paused) {
        return std::chrono::duration_cast<Duration>(_pause_point - _start_point).count();
    } else {
        return std::chrono::duration_cast<Duration>(std::chrono::steady_clock::now() - _start_point).count();
    }
}

}