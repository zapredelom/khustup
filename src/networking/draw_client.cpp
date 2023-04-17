#include "networking/draw_update_raw_data.h"
#include "networking/draw_client.h"

#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>


using boost::asio::ip::tcp;

typedef std::deque<DrawUpdateRawData> DrawUpdateRawData_queue;

DrawClient::DrawClient(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints)
    : io_context_(io_context), socket_(io_context) {
    do_connect(endpoints);
}
void DrawClient::write(const khustup::models::DrawUpdate& msg) {
    std::cout<<"to network and beyound\n";
    const auto& points = msg.getPoints();
    int offset = 0;
    char* data = write_msg_.body();
    for(const auto& point : points) {
        const auto& color = point.getColor();
        memcpy(data + offset, &color.R, sizeof(uint8_t));
        offset += sizeof(uint8_t);
        memcpy(data + offset, &color.G, sizeof(uint8_t));
        offset += sizeof(uint8_t);
        memcpy(data + offset, &color.B, sizeof(uint8_t));
        offset += sizeof(uint8_t);

        bool isOn = point.isOn();
        memcpy(data + offset, &isOn, sizeof(bool));
        offset += sizeof(bool);

        const auto& coord = point.getCoorodinate();
        auto x = coord.x();
        auto y = coord.y();
        memcpy(data + offset, &x, sizeof(int));
        offset += sizeof(int);
        memcpy(data + offset, &y, sizeof(int));
        offset += sizeof(int);

    }
    write_msg_.body_length(offset);
    write_msg_.encode_header();
    write(write_msg_);

}

void DrawClient::write(const DrawUpdateRawData& msg) {
    boost::asio::post(io_context_, [this, msg]() {
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress) {
            do_write();
        }
    });
}

void DrawClient::close() {
    boost::asio::post(io_context_, [this]() { socket_.close(); });
}

void DrawClient::do_connect(const tcp::resolver::results_type& endpoints) {
    boost::asio::async_connect(socket_, endpoints, [this](boost::system::error_code ec, tcp::endpoint) {
        if (!ec) {
            do_read_header();
        }
    });
}

void DrawClient::do_read_header() {
    boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), DrawUpdateRawData::header_length),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec && read_msg_.decode_header()) {
                                    do_read_body();
                                } else {
                                    socket_.close();
                                }
                            });
}

void DrawClient::do_read_body() {
    boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec) {
                                    notifyOnReadCallback();
                                    //std::cout.write(read_msg_.body(), read_msg_.body_length());
                                    //std::cout << "\n";
                                    do_read_header();
                                } else {
                                    socket_.close();
                                }
                            });
}

void DrawClient::do_write() {
    boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (!ec) {
                                    std::cout<<"no issues on writing\n";
                                     write_msgs_.pop_front();
                                     if (!write_msgs_.empty()) {
                                         do_write();
                                     }
                                 } else {
                                    std::cout<<"issues on writing\n";
                                    char buff[4096];
                                    ec.message(buff, 4095);
                                    std::cout<<buff<<std::endl;
                                    socket_.close();
                                 }
                             });
}

void DrawClient::notifyOnReadCallback() {
    if (_onReadCallback) {
        char* body = read_msg_.body();
        khustup::models::Color color;
        bool isOn;
        int x  = -1, y = -1;
        auto iteration_size = 3*sizeof(uint8_t) + sizeof(bool) + 2 * sizeof(int);
        std::vector<khustup::models::DrawPoint> points;
        for (int i = 0; i < read_msg_.body_length(); i += iteration_size) {
            int offset = 0;
            color.R = body[i + offset];
            offset += sizeof(uint8_t);
            color.G = body[i + offset];
            offset += sizeof(uint8_t);
            color.B = body[i + offset];
            offset += sizeof(uint8_t);
            isOn = body[i + offset];
            offset += sizeof(bool);
            x = *( reinterpret_cast<int*>(body + i + offset));
            offset += sizeof(int);
            y = *( reinterpret_cast<int*>(body + i + offset));
            points.emplace_back(khustup::models::DrawPoint({x,y},isOn,color));
        }

        _onReadCallback(std::make_shared<khustup::models::DrawUpdate>(points,khustup::utils::Clock::now()));
    }
}


