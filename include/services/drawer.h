#pragma once

#include "models/draw_canvas.h"
#include "services/draw_update_observer.h"
namespace khustup::models {
class DrawUpdate;
class DrawCanvas;
}

namespace khustup::services {

class Drawer: public IDrawUpdateObserver {
public:
    Drawer(khustup::models::DrawCanvas& cavas) noexcept;
    Drawer(Drawer&&) noexcept = default;
    Drawer& operator=(Drawer&&) noexcept = default;
    ~Drawer() noexcept = default;

    Drawer(const Drawer&) noexcept = delete;
    Drawer& operator=(const Drawer&) noexcept = delete;

    void update(const khustup::models::DrawUpdate& update) noexcept;

private:
    khustup::models::DrawCanvas& _canvas;
};

}  // namespace khustup::services