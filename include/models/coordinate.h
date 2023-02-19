#pragma once
namespace khustup::models
{
    class Coordinate
    {
    public:
        Coordinate(int x, int y) noexcept;
        Coordinate(const Coordinate&) noexcept;

        [[nodiscard]] constexpr int x() const noexcept { return _x; }
        [[nodiscard]] constexpr int y() const noexcept { return _y;}

        private:
            int _x;
            int _y;
    };
} // namespace name
