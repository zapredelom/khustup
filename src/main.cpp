// #include <QApplication>
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
// #include "services/rpi/rpi_drawer.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "services/scale_decorator.h"
// #include "ui/draw_main_window.h"
#include "networking./draw_client.h"
#include "utils/measurer.h"

using namespace std::chrono_literals;
static constexpr int canvasHeight = 1024;
static constexpr int canvaesWidth = 1024;
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
            mat.at<cv::Vec3b>(point.getCoorodinate().y(), point.getCoorodinate().x()) = {
                point.getColor().R, point.getColor().G, point.getColor().B};
            // colors[point.getCoorodinate().y() % canvaesWidth];
        }
        cv::imshow("canvas", mat);
        cv::waitKey(1);
    }

private:
    std::vector<cv::Vec3b> generateColors(int count) {
        std::vector<cv::Vec3b> colors;
        colors.reserve(count);
        for (int i = 0; i < count; ++i) {
            colors.emplace_back(int(std::abs(512 * ((float(i) / (count)-0.5)))), int(255 - 255 * (float(i) / count)),
                                int(255 * (float(i) / count)));
        }
        return colors;
    }
};
using namespace boost::asio;
using ip::tcp;

int main(int argc, char* argv[]) {
  std::cout<<"entering main"<<std::endl;
    // khustup::models::DrawCanvas canvas(canvasHeight, canvaesWidth);
    // khustup::services::Drawer drawer(canvas);
    // CvShow cvShow;
    // //khustup::services::rpi::RpiDrawObserver rpiDrawer(rpiHeight, rpiWidth);
    // //khustup::services::ScaleDecorator scaler(&rpiDrawer, canvasHeight, canvaesWidth, rpiHeight, rpiWidth);
    // //khustup::simulation::WebCamReader simulation(canvasHeight, canvaesWidth, 15); // there is issue with reading
    // camera

    // khustup::simulation::Simulation simulation(canvasHeight, canvaesWidth, 15);

    // simulation.addObserver(&drawer);
    // simulation.addObserver(&cvShow);
    // //simulation.addObserver(&scaler);
    // //rpiDrawer.setBrightness(20);

    // simulation.start(simDuration);
    // std::this_thread::sleep_for(30s);

    try {
        if (argc != 3) {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(argv[1], argv[2]);
        DrawClient c(io_context, endpoints);

        std::thread t([&io_context]() { io_context.run(); });

        char* line = new char[DrawUpdateRawData::max_body_length + 1];
        while (std::cin.getline(line, DrawUpdateRawData::max_body_length + 1)) {
            DrawUpdateRawData msg;
            msg.body_length(std::strlen(line));
            std::memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            c.write(msg);
        }

        c.close();
        t.join();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
