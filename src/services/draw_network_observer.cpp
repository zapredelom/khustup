#include "services/draw_network_observer.h"
#include "networking/draw_client.h"

#include <boost/asio.hpp>
#include <string>
namespace khustup::models {
class DrawUpdate;
}

using namespace khustup::services;

DrawNetworkObserver::DrawNetworkObserver(const std::string& host,const std::string& port)
    : _host(host),
      _port(port),
      _resolver(_io_context),
      _client(_io_context, _resolver.resolve(_host, _port)) {
        _io_context_thread = std::thread([&]() { _io_context.run(); });
      }


DrawNetworkObserver::~DrawNetworkObserver() noexcept {
    _client.close();
    _io_context.stop();
    _io_context_thread.join();
}

void DrawNetworkObserver::update(const khustup::models::DrawUpdate& update) noexcept {
    _client.write(update);
}
