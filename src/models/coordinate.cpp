#include "models/coordinate.h"

using namespace khustup::models;

Coordinate::Coordinate(int x, int y) noexcept : _x(x), _y(y) {}

Coordinate::Coordinate(const Coordinate& other) noexcept : Coordinate(other._x, other._y) {}