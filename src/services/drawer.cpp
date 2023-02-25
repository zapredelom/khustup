#include "services/drawer.h"

#include <iostream>

#include "models/draw_canvas.h"
#include "models/draw_point.h"
#include "models/draw_update.h"

using namespace khustup::services;
Drawer::Drawer(khustup::models::DrawCanvas& canvas) noexcept : _canvas(canvas) {}

void Drawer::update(const khustup::models::DrawUpdate& update) noexcept {
    for (const auto& point : update.getPoints()) {
        auto x = point.getCoorodinate().x();
        auto y = point.getCoorodinate().y();
        _canvas.setPixel(x, y, point.isOn());
    }
}
