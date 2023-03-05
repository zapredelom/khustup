#include "services/scale_decorator.h"
#include "models/draw_update.h"

#include <cassert>
#include <cmath>

using namespace khustup::services;
ScaleDecorator::ScaleDecorator(IDrawUpdateObserver* wrappee, int inputHeight, int inputWidth, int outputHeight, int outputWidth)
    : _wrappee(wrappee)
    , _inputHeight(inputHeight)
    , _inputWidth(inputWidth)
    , _outputHeight(outputHeight)
    , _outputWidth(outputWidth) {
        assert(_wrappee != nullptr);
    }

void ScaleDecorator::update(const khustup::models::DrawUpdate& update) noexcept {
    auto updated = doScale(update);
    _wrappee->update(updated);
}

khustup::models::DrawUpdate ScaleDecorator::doScale(const khustup::models::DrawUpdate& update) noexcept {
    float heightScale = float(_outputHeight) / float(_inputHeight);
    float widthScale = float(_outputWidth) / float(_inputWidth);

    std::vector<khustup::models::DrawPoint> updated;
    updated.reserve(update.getPoints().size());

    auto singlePointScaler  = [&] (const khustup::models::DrawPoint& point) -> khustup::models::DrawPoint {
                float x = point.getCoorodinate().x();
                float y = point.getCoorodinate().y();
                auto coordinate = khustup::models::Coordinate{int(std::lroundf(x * widthScale)), int(std::lroundf(y * widthScale))};
                return khustup::models::DrawPoint{coordinate, point.isOn(), point.getColor()};
            };
    std::ranges::transform(update.getPoints(), std::back_inserter(updated), singlePointScaler);
    
    return {updated, update.getTimeStamp()};
}