#include "services/draw_network_observer.h"

using namespace khustup::services;


void DrawNetworkObserver::update(const khustup::models::DrawUpdate& update) noexcept {
    std::cout << "DrawNetworkObserver::update" << std::endl;
}
