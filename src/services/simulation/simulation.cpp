#include "services/simulation/simulation.h"

#include <thread>

#include "models/coordinate.h"
#include "utils/measurer.h"
using namespace khustup::simulation;

Simulation::Simulation(int height, int width, int updateFrequency) noexcept
    : _height(height),
      _width(width),
      _gen(_rd()),
      _keep_sumulating(false),
      _frequency(updateFrequency),
      _dis_init(0, height),
      _dis_draw(-_step, _step),
      _0_1(0, 1),
      _dist_color(50, 200),
      _lastCoordinate({_height / 2, _width / 2}) {}

void Simulation::start(uint64_t simulationDurationInMilliseconds) noexcept {
    _keep_sumulating = true;
    _simulation_thread = std::thread([this, simulationDurationInMilliseconds]() {
        khustup::utils::Measurer measurer;
        while (_keep_sumulating && measurer.getElapsedTimeInMilliseconds() <= simulationDurationInMilliseconds) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / _frequency));
            notifyAll(generate_random_draw_update_model());
        }
    });
}

Simulation::~Simulation() noexcept {
    //_keep_sumulating = false;
    if (_simulation_thread.joinable()) {
        _simulation_thread.join();
    }
}

khustup::models::DrawUpdate Simulation::generate_random_draw_update_model() noexcept {
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
        auto color =
            khustup::models::Color{uint8_t(_dist_color(_gen)), uint8_t(_dist_color(_gen)), uint8_t(_dist_color(_gen))};
        return khustup::models::DrawPoint{khustup::models::Coordinate(x, y), true, color};
        // return khustup::models::Coordinate(last.x() + x_direction, last.y() + y_direction);
    });
    _lastCoordinate = coordinates.back();
    return khustup::models::DrawUpdate(coordinates, khustup::utils::Clock::now());
}

khustup::models::DrawUpdate Simulation::gen_arrow() noexcept {
    std::vector<khustup::models::DrawPoint> coordinates;
    for (int i = 0; i < _width; i++)
        for (int j = 0; j < _width; j++) {
            if ((i > 4 && i < 8) && ((j > 4 && j < 8)) || (i > 10 && i < 16) && ((j > 10 && j < 16))) {
                auto color = khustup::models::Color{0, uint8_t(_dist_color(_gen)), uint8_t(_dist_color(_gen))};
                coordinates.emplace_back(khustup::models::Coordinate(i, j), true, color);
            }
        }
    return khustup::models::DrawUpdate(coordinates, khustup::utils::Clock::now());
}
