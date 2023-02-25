#include "models/draw_point.h"

#include <type_traits>

using namespace khustup::models;

DrawPoint::DrawPoint(const Coordinate& coordinate, bool isOn) noexcept
    : _coordinate(coordinate), _isOn(isOn) {}


Coordinate DrawPoint::getCoorodinate() const noexcept { return _coordinate; }



