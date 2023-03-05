#pragma once

#include "services/draw_update_subject.h"
#include "models/draw_update.h"

#include <thread>
#include <opencv2/core.hpp>

namespace khustup::simulation {
class WebCamReader: public khustup::services::IDrawUpdateSubject {
public:
    WebCamReader(int height, int width, int fps = 15);
    WebCamReader(const WebCamReader& ) = delete;

    void start(uint64_t simulationDurationInMilliseconds = 1000) noexcept;

    ~WebCamReader();

private:
    khustup::models::DrawUpdate cvMatToUpdateModel(const cv::Mat& mat);

private:
    int _height;
    int _width;
    int _fps;
    std::thread _simulation_thread;
};
}