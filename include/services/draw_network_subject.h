#include "services/draw_update_subject.h"
#include "networking/draw_client.h"

#include <boost/asio.hpp>

#include <string>
namespace khustup::models {
class DrawUpdate;
}

namespace khustup::services {
class DrawNetworkSubject : public IDrawUpdateSubject {
public:
    DrawNetworkSubject(const std::string &host, const std::string &port) noexcept;
    ~DrawNetworkSubject();

private:
    std::string _host;
    std::string _port;
    boost::asio::io_context _io_context;
    boost::asio::ip::tcp::resolver _resolver;
    std::thread _io_context_thread;
    DrawClient _client;

};
}
