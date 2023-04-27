#include "services/draw_network_subject.h"
#include <boost/asio.hpp>


using namespace khustup::services;

DrawNetworkSubject::DrawNetworkSubject(const std::string &host, const std::string &port) noexcept
    : _host(host),
      _port(port),
      _resolver(_io_context),
      _client(_io_context, _resolver.resolve(_host, _port)) {
        _io_context_thread = std::thread([&]() { _io_context.run(); });
        _client.setOnReadCallback([this](DrawUpdatePtr update) {
            notifyAll(*update);
        });
      }


DrawNetworkSubject::~DrawNetworkSubject() {
    _client.close();
    _io_context.stop();
    _io_context_thread.join();
}

