#pragma once
namespace khustup::models {
class DrawUpdate;
}  // namespace khustup::models


namespace khustup::services {
class IDrawUpdateObserver {
public:
    IDrawUpdateObserver() noexcept = default;
    IDrawUpdateObserver(IDrawUpdateObserver&&) noexcept = default;
    IDrawUpdateObserver(const IDrawUpdateObserver&) noexcept = delete;

    IDrawUpdateObserver& operator=(IDrawUpdateObserver&&) noexcept = default;
    IDrawUpdateObserver& operator=(const IDrawUpdateObserver&) noexcept = delete;

    virtual ~IDrawUpdateObserver() noexcept = default;

    virtual void update(const khustup::models::DrawUpdate& update) noexcept = 0;
};
}  // namespace khustup:services
