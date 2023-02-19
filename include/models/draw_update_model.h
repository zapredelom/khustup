#pragma once

#include "models/draw_point_model.h"
#include "utils/type_aliases.h"

namespace khustup::models {
class DrawUpdate {
    using TimeStamp = khustup::utils::TimeStamp;

public:
    DrawUpdate() noexcept;
    DrawUpdate(const DrawUpdate&) noexcept = delete;
    DrawUpdate(DrawUpdate&&) noexcept;
    DrawUpdate(const std::vector<DrawPoint>& points, TimeStamp timeStamp) noexcept;

    [[nodiscard]] const std::vector<DrawPoint>& getPoints() const noexcept;

    [[nodiscard]] TimeStamp getTimeStamp() const noexcept;
    [[nodiscard]] int pointCount() const noexcept;

    ~DrawUpdate() noexcept = default;

private:
    std::vector<DrawPoint> _points;
    TimeStamp _timeStamp;
};
}  // namespace kustup
