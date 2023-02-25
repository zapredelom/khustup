#pragma once

#include "models/coordinate.h"
namespace khustup::models {
class DrawPoint {
public:
    DrawPoint(const DrawPoint&) noexcept = default;
    DrawPoint(const Coordinate& coordinate, bool isOn = true) noexcept;

    [[nodiscard]] Coordinate getCoorodinate() const noexcept;
    constexpr bool isOn() const noexcept { return _isOn; }

    ~DrawPoint() noexcept = default;

private:
    Coordinate _coordinate;
    bool _isOn;
};
}  // namespace khustup
