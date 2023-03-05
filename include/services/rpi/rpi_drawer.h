#pragma once

#include "services/draw_update_observer.h"

#include "ws2811.h"

#include <vector>
namespace khustup::models{
    class DrawUpdate;
    class DrawPoint;
}
namespace khustup::services::rpi {
class RpiDrawObserver : public IDrawUpdateObserver {
public:
    RpiDrawObserver(int height, int width);

    void update(const khustup::models::DrawUpdate& update) noexcept override;
    void setBrightness(uint8_t brightness) noexcept;

    ~RpiDrawObserver();

private:
    [[nodiscard]] ws2811_t initLedString() const noexcept;
    void updateInternalStorage(const khustup::models::DrawUpdate& update);
    void updateLedStrip(const khustup::models::DrawUpdate& update);
    int transformCoordinateToSingleIndex(const khustup::models::DrawPoint& point);
    void clearInternalAndString();


private:
    int _height;
    int _width;
    int _led_count;
    int _strip_type;
    int _gpio_pin_num;
    int _dma_num;
    uint8_t _brightness;
    std::vector<ws2811_led_t> _matrix;
    ws2811_t _led_string;

private:
    static constexpr int kDefaultGpioPinNum = 18;
    static constexpr int kDefaultDmaNum = 10;
    static constexpr uint8_t kDefaultBrightness = 255;
    static constexpr ws2811_led_t kBalckColor = 0;
    static constexpr ws2811_led_t kWhihteColor = 0x00101010;

};
}