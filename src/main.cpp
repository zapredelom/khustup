//#include <QApplication>
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
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "services/scale_decorator.h"
//#include "ui/draw_main_window.h"
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

  try
  {

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
      resolver.resolve("", "1234");

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);
    boost::system::error_code error;
    boost::array<char, 5> buf{'h','e','l','l','o'};
    socket.write_some(boost::asio::buffer(buf), error);



  //   for (;;)
  //   {
  //     boost::array<char, 300> buf;

  //     size_t len = socket.read_some(boost::asio::buffer(buf), error);

  //     if (error == boost::asio::error::eof)
  //       break; // Connection closed cleanly by peer.
  //     else if (error)
  //       throw boost::system::system_error(error); // Some other error.

  //     std::cout.write(buf.data(), len);
  //     std::cout<<std::endl;
  //   }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

    return 0;
}
