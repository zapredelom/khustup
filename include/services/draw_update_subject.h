#pragma once
#include <unordered_set>
#include <vector>

namespace khustup::models {
class DrawUpdate;
}  // namespace khustup::models
namespace khustup::services {
class IDrawUpdateObserver;
class IDrawUpdateSubject {
public:
    IDrawUpdateSubject() noexcept = default;
    IDrawUpdateSubject(IDrawUpdateSubject&&) noexcept = default;
    IDrawUpdateSubject(const IDrawUpdateSubject&) noexcept = delete;

    IDrawUpdateSubject& operator=(IDrawUpdateSubject&&) noexcept = default;
    IDrawUpdateSubject& operator=(const IDrawUpdateSubject&) noexcept = delete;

    virtual ~IDrawUpdateSubject() noexcept = default;

    virtual void notifyAll(const khustup::models::DrawUpdate& update) noexcept;
    virtual void addObserver(IDrawUpdateObserver* observer) noexcept;
    virtual void removeObserver(IDrawUpdateObserver* observer) noexcept;

private:
    std::unordered_set<IDrawUpdateObserver*> _observers;
};
}  // namespace khustup::services
