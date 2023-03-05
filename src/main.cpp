#include <algorithm>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <ranges>
#include <thread>
#include <type_traits>

#include "services/draw_update_observer.h"
#include "services/drawer.h"
#include "services/simulation/simulation.h"
#include "services/simulation/webcam_reader.h"
#include "services/rpi/rpi_drawer.h"
#include "services/scale_decorator.h"
#include "utils/measurer.h"

using namespace std::chrono_literals;
static constexpr int canvasHeight = 360;
static constexpr int canvaesWidth = 440;
static constexpr int rpiHeight = 16;
static constexpr int rpiWidth = 16;
static constexpr int simDuration = 30000;

class CvShow : public khustup::services::IDrawUpdateObserver {
public:
    void update(const khustup::models::DrawUpdate& update) noexcept override {
        static cv::Mat mat(canvasHeight, canvaesWidth, CV_8UC3, cv::Scalar(0, 0, 0));
        static std::vector<cv::Vec3b> colors = generateColors(canvaesWidth);
        int count = 0;
        for (auto& point : update.getPoints()) {
            mat.at<cv::Vec3b>(point.getCoorodinate().y(), point.getCoorodinate().x()) = {point.getColor().R, point.getColor().G, point.getColor().B};
                //colors[point.getCoorodinate().y() % canvaesWidth];
        }
	cv::imshow("canvas", mat);
	cv::waitKey(1);
    }

private:
    std::vector<cv::Vec3b> generateColors(int count) {
        std::vector<cv::Vec3b> colors;
        colors.reserve(count);
        for (int i = 0; i < count; ++i) {
            colors.emplace_back(std::abs(512 * ((float(i) / (count)-0.5))), 
                                255 - 255 * (float(i) / count),
                                255 * (float(i) / count));
        }
        return colors;
    }
};

int main() {

    khustup::models::DrawCanvas canvas(canvasHeight, canvaesWidth);
    khustup::services::Drawer drawer(canvas);
    CvShow cvShow;
    khustup::services::rpi::RpiDrawObserver rpiDrawer(rpiHeight, rpiWidth);
    khustup::services::ScaleDecorator scaler(&rpiDrawer, canvasHeight, canvaesWidth, rpiHeight, rpiWidth);

    //khustup::simulation::WebCamReader simulation(canvasHeight, canvaesWidth, 15); // there is issue with reading camera
    khustup::simulation::Simulation simulation(canvasHeight, canvaesWidth, 15);

    simulation.addObserver(&drawer);
    simulation.addObserver(&cvShow);
    simulation.addObserver(&scaler);
    rpiDrawer.setBrightness(20);

    simulation.start(simDuration);
    std::this_thread::sleep_for(30s);

    return 0;
}

