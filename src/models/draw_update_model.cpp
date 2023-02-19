#include <vector>

#include "models/draw_update_model.h"
using namespace khustup::models;

namespace km {
using TimeStamp = khustup::utils::TimeStamp;
using Clock = khustup::utils::Clock;
}
DrawUpdate::DrawUpdate() noexcept : _timeStamp(km::Clock::now()) {}

DrawUpdate::DrawUpdate(const std::vector<DrawPoint>& points, km::TimeStamp timeStamp) noexcept
    : _points(points), _timeStamp(timeStamp) {}

DrawUpdate::DrawUpdate(DrawUpdate&& other) noexcept : _points(std::move(other._points)), _timeStamp(other._timeStamp) {}

const std::vector<DrawPoint>& DrawUpdate::getPoints() const noexcept { return _points; }

km::TimeStamp DrawUpdate::getTimeStamp() const noexcept { return _timeStamp; }

int DrawUpdate::pointCount() const noexcept { return _points.size(); }
