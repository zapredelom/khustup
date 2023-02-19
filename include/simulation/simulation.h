#pragma once

#include <functional>
#include <random>

#include "models/draw_update_model.h"
#include "utils/measurer.h"
#include "utils/type_aliases.h"

template <typename T>
concept DrawUpdateHandler = std::is_invocable_r_v<void, T, khustup::models::DrawUpdate>;

namespace khustup::simulation {
template <DrawUpdateHandler Ty_DrawUpdateHandler = std::function<void(khustup::models::DrawUpdate)>>
class Simulation {
public:
    Simulation() noexcept {
    }
    Simulation(const Simulation&) noexcept = delete;

    void setDrowUpdateHandler(Ty_DrawUpdateHandler&& drawUpdateHandler) noexcept {
        _drawUpdateHandler = drawUpdateHandler;
    }

    void start(uint64_t simulationDurationInMilliseconds = 1000) noexcept {
        _keep_sumulating = true;
        _simulation_thread = std::thread([this, simulationDurationInMilliseconds]() {
            khustup::utils::Measurer measurer;
            while (_keep_sumulating && measurer.getElapsedTimeInMilliseconds() <= simulationDurationInMilliseconds) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                _drawUpdateHandler(generate_random_draw_update());
            }
        });
    }

    ~Simulation() noexcept {
        //_keep_sumulating = false;
        if (_simulation_thread.joinable()) {
            _simulation_thread.join();
        }
    }

private:
    khustup::models::DrawUpdate generate_random_draw_update() noexcept {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis_init(0, 4096);
        std::uniform_int_distribution<> dis_draw(-1, 1);
        khustup::models::Coordinate initialCoordinate(dis_init(gen), dis_init(gen));
        std::vector<khustup::models::DrawPoint> coordinates;
        coordinates.push_back(initialCoordinate);
        std::generate_n(std::back_inserter(coordinates), 100, [&]() {
            return khustup::models::Coordinate(coordinates.back().getCoorodinate().x() + dis_draw(gen),
                                               coordinates.back().getCoorodinate().y() + dis_draw(gen));
        });
        return khustup::models::DrawUpdate(coordinates, std::chrono::steady_clock::now());
    }

private:
    Ty_DrawUpdateHandler _drawUpdateHandler;
    bool _keep_sumulating;
    std::thread _simulation_thread;
};

}  // namespace khustup:simulation
