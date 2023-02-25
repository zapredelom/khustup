#pragma once

#include <functional>
#include <random>

#include "models/draw_update.h"
#include "utils/measurer.h"
#include "utils/type_aliases.h"
#include "services/draw_update_subject.h"


namespace khustup::simulation {
class Simulation : public khustup::services::IDrawUpdateSubject{
public:
    Simulation(int height = 4096, int width = 4096, int updateFrequency = _default_frequency) noexcept
        : _height(height),
          _width(width),
          _gen(_rd()),
          _keep_sumulating(false),
          _frequency(updateFrequency),
          _dis_init(0, height),
          _dis_draw(-_step, _step),
          _0_1(0, 1),
          _lastCoordinate(_height / 2, _width / 2) {}
    Simulation(const Simulation&) noexcept = delete;

    void start(uint64_t simulationDurationInMilliseconds = 1000) noexcept {
        _keep_sumulating = true;
        _simulation_thread = std::thread([this, simulationDurationInMilliseconds]() {
            khustup::utils::Measurer measurer;
            while (_keep_sumulating && measurer.getElapsedTimeInMilliseconds() <= simulationDurationInMilliseconds) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000 / _frequency));
                notifyAll(generate_random_draw_update_model());
            }
        });
    }

    ~Simulation() noexcept override {
        //_keep_sumulating = false;
        if (_simulation_thread.joinable()) {
            _simulation_thread.join();
        }
    }

private:
    khustup::models::DrawUpdate generate_random_draw_update_model() noexcept {
        std::vector<khustup::models::DrawPoint> coordinates;
        coordinates.push_back(_lastCoordinate);
        auto x_direction = _dis_draw(_gen);
        auto y_direction = _dis_draw(_gen);
        std::generate_n(std::back_inserter(coordinates), _draw_points_count_per_update, [&]() {
            auto last = coordinates.back().getCoorodinate();
            auto x = last.x() + _0_1(_gen) * x_direction;
            auto y = last.y() + _0_1(_gen) * y_direction;

            x = std::abs(x) % _width;
            y = std::abs(y) % _height;
            return khustup::models::Coordinate(x,y);
            // return khustup::models::Coordinate(last.x() + x_direction, last.y() + y_direction);
        });
        _lastCoordinate = coordinates.back().getCoorodinate();
        return khustup::models::DrawUpdate(coordinates, khustup::utils::Clock::now());
    }

private:
    int _height;
    int _width;
    bool _keep_sumulating;
    int _frequency;
    std::thread _simulation_thread;

    std::random_device _rd;
    std::mt19937 _gen;
    std::uniform_int_distribution<> _dis_init;
    std::uniform_int_distribution<> _dis_draw;
    std::uniform_int_distribution<> _0_1;

    khustup::models::Coordinate _lastCoordinate;

private:
    static constexpr int _draw_points_count_per_update = 100;
    static constexpr int _default_frequency = 100;
    static constexpr int _step = 1;
};

}  // namespace khustup:simulation
