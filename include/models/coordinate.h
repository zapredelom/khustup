#pragma once
#include "utils/type_aliases.h"
namespace khustup::models
{
    class Coordinate
    {
    public:
        Coordinate(khustup::utils::CoordinateType x, khustup::utils::CoordinateType y) noexcept;
        Coordinate(const Coordinate&) noexcept;

        [[nodiscard]] constexpr khustup::utils::CoordinateType x() const noexcept { return _x; }
        [[nodiscard]] constexpr khustup::utils::CoordinateType y() const noexcept { return _y;}

        private:
            khustup::utils::CoordinateType _x;
            khustup::utils::CoordinateType _y;
    };
} // namespace name
