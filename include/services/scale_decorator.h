#pragma once

#include "services/draw_update_observer.h"
#include "models/draw_update.h"

#include <algorithm>
#include <ranges>

namespace khustup::models{
    class DrawUpdate;
}

namespace khustup::services {
    class ScaleDecorator: public IDrawUpdateObserver {
    public:
        ScaleDecorator(IDrawUpdateObserver* wrappee, int inputHeight, int inputWidth, int outputHeight, int outputWidth);
        void update(const khustup::models::DrawUpdate& update) noexcept override;
    
    private:
        khustup::models::DrawUpdate doScale(const khustup::models::DrawUpdate& update) noexcept;

    private:
        IDrawUpdateObserver* _wrappee;
        int _inputHeight;
        int _inputWidth;
        int _outputHeight;
        int _outputWidth;
    };
}