#pragma once
#include "networking/draw_client.h"
#include "services/draw_update_observer.h"
#include <boost/asio.hpp>


namespace khustup::models {
    class DrawUpdate;
}  // namespace khustup::models

namespace khustup::services {
    class DrawNetworkObserver : public IDrawUpdateObserver {
    public:
        DrawNetworkObserver(const std::string& host, const std::string& port) ;
        DrawNetworkObserver(DrawNetworkObserver&&) noexcept = default;
        DrawNetworkObserver& operator=(DrawNetworkObserver&&) noexcept = default;

        DrawNetworkObserver(const DrawNetworkObserver&) noexcept = delete;
        DrawNetworkObserver& operator=(const DrawNetworkObserver&) noexcept = delete;

        virtual ~DrawNetworkObserver() noexcept ;

        virtual void update(const khustup::models::DrawUpdate& update) noexcept override;
        private:
        std::string _host;
        std::string _port;
        boost::asio::io_context _io_context;
        boost::asio::ip::tcp::resolver _resolver;
        std::thread _io_context_thread;
        DrawClient _client;
        
    };
}  // namespace khustup::services
