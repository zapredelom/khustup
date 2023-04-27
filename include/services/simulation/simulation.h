#pragma once

#include "models/draw_update.h"
#include "utils/type_aliases.h"
#include "services/draw_update_subject.h"
#include "utils/type_aliases.h"


#include <functional>
#include <random>
#include <thread>

namespace khustup::simulation {
class Simulation : public khustup::services::IDrawUpdateSubject{
public:
    Simulation(khustup::utils::CoordinateType height = 4096, khustup::utils::CoordinateType width = 4096, int updateFrequency = _default_frequency) noexcept;
    Simulation(const Simulation&) noexcept = delete;

    void start(uint64_t simulationDurationInMilliseconds = 1000) noexcept;

    ~Simulation() noexcept override;
private:
    khustup::models::DrawUpdate generate_random_draw_update_model() noexcept ;

     khustup::models::DrawUpdate gen_arrow() noexcept;

private:
    khustup::utils::CoordinateType _height;
    khustup::utils::CoordinateType _width;
    bool _keep_sumulating;
    int _frequency;
    std::thread _simulation_thread;

    std::random_device _rd;
    std::mt19937 _gen;
    std::uniform_int_distribution<> _dis_init;
    std::uniform_int_distribution<> _dis_draw;
    std::uniform_int_distribution<> _0_1;
    std::uniform_int_distribution<unsigned short> _dist_color;

    khustup::models::DrawPoint _lastCoordinate;

private:
    static constexpr int _draw_points_count_per_update = 1000;
    static constexpr int _default_frequency = 10;
    static constexpr int _step = 1;
};

}  // namespace khustup:simulation
