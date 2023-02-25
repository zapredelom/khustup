#include "services/draw_update_subject.h"

#include "models/draw_update.h"
#include "services/draw_update_observer.h"

namespace khustup::services {

void IDrawUpdateSubject::notifyAll(const khustup::models::DrawUpdate& update) noexcept {
    for (auto observer : _observers) {
        observer->update(update);
    }
}

void IDrawUpdateSubject::addObserver(IDrawUpdateObserver* observer) noexcept {
    _observers.insert(observer);
}

void IDrawUpdateSubject::removeObserver(IDrawUpdateObserver* observer) noexcept {
    _observers.erase(observer);
}
}  // namespace khustup::services