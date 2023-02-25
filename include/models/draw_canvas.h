#pragma once

#include <vector>

namespace khustup::models {

class DrawCanvas {
public:
    DrawCanvas(int hegith, int width);
    DrawCanvas(DrawCanvas&&) noexcept = default;
    DrawCanvas& operator=(DrawCanvas&&) noexcept = default;
    ~DrawCanvas() noexcept = default;

    DrawCanvas(const DrawCanvas&) noexcept = delete;
    DrawCanvas& operator=(const DrawCanvas&) noexcept = delete;

    [[nodiscard]] constexpr int getWidth() const noexcept { return _width; }
    [[nodiscard]] constexpr int getHeight() const noexcept { return _height; }

    void setPixel(int x, int y, bool isOn) noexcept;
    [[nodiscard]] bool getPixel(int x, int y) const noexcept;

    void clear() noexcept;

private:
    int _width;
    int _height;
    std::vector<int> _pixels;
};
}  // namespace khustup::model
