#include "services/draw_network_observer.h"
#include <boost/asio.hpp>


using namespace khustup::services;

DrawNetworkSubject::DrawNetworkSubject(const std::string &host, const std::string &port) noexcept
    : _host(host), _port(port), _resolver(_io_context), _io_context_thread([this]() { _io_context.run(); }),
      _client(_io_context, _resolver.resolve(_host, _port)) {}


DrawNetworkSubject::~DrawNetworkSubject() {
    _io_context.stop();
    _io_context_thread.join();
}

