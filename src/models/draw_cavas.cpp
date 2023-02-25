#include <algorithm>
#include <ranges>

#include "models/draw_canvas.h"

using namespace khustup::models;

DrawCanvas::DrawCanvas(int height, int width) : _width(width), _height(height), _pixels(height * width) {}



void DrawCanvas::setPixel(int x, int y, bool isOn) noexcept {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    _pixels[y * _width + x] = isOn;
}

[[nodiscard]] bool DrawCanvas::getPixel(int x, int y) const noexcept {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    }
    return _pixels[y * _width + x];
}

void DrawCanvas::clear() noexcept { std::ranges::fill(_pixels, false); }