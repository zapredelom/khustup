#pragma once

#include "models/coordinate.h"
#include "models/color.h"
namespace khustup::models {
class DrawPoint {
public:
    DrawPoint(const DrawPoint&) noexcept = default;
    DrawPoint(const Coordinate& coordinate, bool isOn = true, const Color& color = {0, 0, 0}) noexcept;

    [[nodiscard]] Coordinate getCoorodinate() const noexcept;
    constexpr bool isOn() const noexcept { return _isOn; }
    constexpr Color getColor() const noexcept { return _color; }
    constexpr void setColor(const Color& color)  noexcept {  _color = color;}


    ~DrawPoint() noexcept = default;

private:
    Coordinate _coordinate;
    bool _isOn;
    Color _color;
};
}  // namespace khustup
