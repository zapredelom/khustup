#include "models/coordinate.h"

using namespace khustup::models;

Coordinate::Coordinate(khustup::utils::CoordinateType x, khustup::utils::CoordinateType y) noexcept : _x(x), _y(y) {}

Coordinate::Coordinate(const Coordinate& other) noexcept : Coordinate(other._x, other._y) {}