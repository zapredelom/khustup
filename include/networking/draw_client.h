#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>

#include "draw_update_raw_data.h"

using boost::asio::ip::tcp;

typedef std::deque<DrawUpdateRawData> DrawUpdateRawData_queue;

class DrawClient {
public:
    DrawClient(boost::asio::io_context& io_context, const boost::asio::ip::tcp::resolver::results_type& endpoints);
    void write(const DrawUpdateRawData& msg);
    void close();

private:
    void do_connect(const boost::asio::ip::tcp::resolver::results_type& endpoints);
    void do_read_header();
    void do_read_body();
    void do_write();

private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    DrawUpdateRawData read_msg_;
    DrawUpdateRawData_queue write_msgs_;
};
