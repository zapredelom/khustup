#include "services/draw_update_subject.h"

namespace khustup::models {
class DrawUpdate;
}

namespace services::sercies {
class DrawNetworkObserver : public IDrawUpdateSubject {
public:
    DrawNetworkObserver() = default;
    ~DrawNetworkObserver() = default;

    void update(const models::DrawUpdate& update) noexcept override;

};
}
