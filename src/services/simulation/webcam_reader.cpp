#include "services/simulation/webcam_reader.h"
#include "utils/measurer.h"
#include "models/coordinate.h"

#include <opencv2/highgui.hpp>
#include <iostream>


using namespace khustup::simulation;

WebCamReader::WebCamReader(int height, int width, int fps) 
 : _height(height)
 , _width(width)
 , _fps(fps)
 {

 }

 void WebCamReader::start(uint64_t simulationDurationInMilliseconds) noexcept {

    _simulation_thread = std::thread( [this, simulationDurationInMilliseconds]() {
        cv::VideoCapture video(0);

	khustup::utils::Measurer m;
        cv::Mat mt;
        video.set(cv::CAP_PROP_FRAME_WIDTH,_width);
        video.set(cv::CAP_PROP_FRAME_HEIGHT,_height);
        video.set(cv::CAP_PROP_FPS, _fps);
        while(m.getElapsedTimeInMilliseconds() < simulationDurationInMilliseconds) {
            video>>mt;
            notifyAll(cvMatToUpdateModel(mt));
        }
    });
 }

WebCamReader::~WebCamReader() {
    if (_simulation_thread.joinable()) {
        _simulation_thread.join();
    }
}
 khustup::models::DrawUpdate WebCamReader::cvMatToUpdateModel(const cv::Mat& mt) {
    khustup::models::DrawUpdate ret;
    std::vector<khustup::models::DrawPoint> points;
    for(int i=0; i<mt.rows; i++)
    for(int j=0; j<mt.cols; j++) 
    {
        khustup::models::Color color{
            mt.at<cv::Vec3b>(i,j)[1],
            mt.at<cv::Vec3b>(i,j)[2],
            mt.at<cv::Vec3b>(i,j)[0],
        };
        khustup::models::Coordinate coo{i,j};
    points.emplace_back(coo, true, color);
    }
    return khustup::models::DrawUpdate(points, khustup::utils::Clock::now());
 }
