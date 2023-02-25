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
#include "utils/measurer.h"

static constexpr int canvasHeight = 64;
static constexpr int canvaesWidth = 64;
static constexpr int simDuration = 30000;

class CvShow : public khustup::services::IDrawUpdateObserver {
public:
    void update(const khustup::models::DrawUpdate& update) noexcept override {
        static cv::Mat mat(canvasHeight, canvaesWidth, CV_8UC3, cv::Scalar(0, 0, 0));
        static std::vector<cv::Vec3b> colors = generateColors(canvaesWidth);
        int count = 0;
        for (auto& point : update.getPoints()) {
            mat.at<cv::Vec3b>(point.getCoorodinate().x(), point.getCoorodinate().y()) =
                colors[point.getCoorodinate().y() % canvaesWidth];
            if (++count > 5) {
                cv::imshow("canvas", mat);
                cv::waitKey(1);
                count = 0;
            }
        }
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

void helperShowCurrentcCanvas(const khustup::models::DrawUpdate& update) {}
int main() {

    khustup::models::DrawCanvas canvas(canvasHeight, canvaesWidth);
    khustup::services::Drawer drawer(canvas);
    CvShow cvShow;

    khustup::simulation::Simulation simulation(canvasHeight, canvaesWidth, 50);

    simulation.addObserver(&drawer);
    simulation.addObserver(&cvShow);

    simulation.start(simDuration);

    return 0;
}

// #define working_code \
//     int ii = 0; while(ii++<2){ \
//     int x = 2;       \
//     int y = 4;       \
//     volatile int z = x + y;};

// class multiplayerBase {
// public:
//     virtual void mul() = 0;
// };

// class multiplayer : public multiplayerBase {
// public:
//     void mul() override { working_code }
// };

// template <typename T>
// void caller(T&& t) {
//     static_assert(std::is_invocable_r_v<void, T>, "T must be invocable");
//     volatile int i = 0;
//     while (i++ < 1) {
//         t();
//     }
// }

// void test() { working_code }

// int main() {
//     khustup::utils::Measurer measurer;

//     measurer.reset();
//     std::function ff([]() { working_code });
//     caller(ff);
//     std::cout << " std::functino " << measurer.getElapsedTimeInMicroseconds() << std::endl;

//     measurer.reset();
//     caller([]() { working_code });
//     std::cout << " lambda " << measurer.getElapsedTimeInMicroseconds() << std::endl;

//     measurer.reset();
//     caller(test);
//     std::cout << " function ptr " << measurer.getElapsedTimeInMicroseconds() << std::endl;

//     measurer.reset();
//     multiplayerBase* mp = new multiplayer();
//     caller([&]() { mp->mul(); });
//     std::cout << " virtual function " << measurer.getElapsedTimeInMicroseconds() << std::endl;
// }