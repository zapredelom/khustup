#include "services/rpi/rpi_drawer.h"
#include "models/draw_update.h"
#include "models/draw_point.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;
using namespace std::string_literals;
using namespace khustup::services::rpi;

RpiDrawObserver::RpiDrawObserver(int height, int width)
    : _height(height)
    , _width(width)
    , _led_count(_height * _width)
    , _strip_type(WS2811_STRIP_GBR)
    , _gpio_pin_num(kDefaultGpioPinNum)
    , _dma_num(kDefaultDmaNum)
    , _brightness(kDefaultBrightness)
    , _matrix(_led_count, kBalckColor)
    , _led_string(initLedString()) {
    ws2811_return_t ret; 
    if ((ret = ws2811_init(&_led_string)) != WS2811_SUCCESS) {
        throw new std::invalid_argument("ws2811_init failed: "s + ws2811_get_return_t_str(ret));
    }
}


void RpiDrawObserver::setBrightness(uint8_t brightness) noexcept {
    _brightness = brightness;
    _led_string.channel[0].brightness = _brightness;
}

void RpiDrawObserver::update(const khustup::models::DrawUpdate& update) noexcept {
    std::cout<<"updating internal" <<std::endl;
    updateInternalStorage(update);
    std::cout<<"updating led strip" <<std::endl;
    updateLedStrip(update);
    std::cout<<"updating done" <<std::endl;
}

RpiDrawObserver::~RpiDrawObserver() {
    clearInternalAndString();
    ws2811_render(&_led_string);
    ws2811_fini(&_led_string);

}
ws2811_t RpiDrawObserver::initLedString() const noexcept {
    return {
        .freq = WS2811_TARGET_FREQ,
        .dmanum = _dma_num,
        .channel =
            {
                [0] =
                    {
                        .gpionum = _gpio_pin_num,
                        .invert = 0,
                        .count = _led_count,
                        .strip_type = _strip_type,
                        .brightness = uint8_t{_brightness},
                    },
                [1] =
                    {
                        .gpionum = 0,
                        .invert = 0,
                        .count = 0,
                        .brightness = 0,
                    },
            },
        };
}

void RpiDrawObserver::updateInternalStorage(const khustup::models::DrawUpdate& update) {
    for(auto point: update.getPoints()) {
        int index = transformCoordinateToSingleIndex(point);
        auto c = point.getColor();
        ws2811_led_t r = 0;
        r |= c.R;
        r <<= 8;
        r |= c.G;
        r <<= 8;
        r |= c.B;
        _matrix[index] = point.isOn() ? r : kBalckColor;
    }
}

void RpiDrawObserver::updateLedStrip(const khustup::models::DrawUpdate& update) {
    for(auto point: update.getPoints()) {
        int index = transformCoordinateToSingleIndex(point);
        auto c = point.getColor();
        ws2811_led_t r = 0;
        r |= c.R;
        r <<= 8;
        r |= c.G;
        r <<= 8;
        r |= c.B;
        _led_string.channel[0].leds[index] =  point.isOn() ? r : kBalckColor;
    }
    std::cout<<"ws render"<<std::endl;
    ws2811_return_t ret;
    if ((ret = ws2811_render(&_led_string)) != WS2811_SUCCESS) {
	std::string st = ws2811_get_return_t_str(ret);
	std::cout<<st<<std::endl;
        throw new std::invalid_argument( "ws2811_render failed: "s + st);
    }
}

int RpiDrawObserver::transformCoordinateToSingleIndex(const khustup::models::DrawPoint& point) {
    int x_mirrored = _width - point.getCoorodinate().x();
    if(point.getCoorodinate().y()&1 != 0){
        return point.getCoorodinate().y() * _width + _width - x_mirrored - 1;
    } else {
        return point.getCoorodinate().y() * _width + x_mirrored;
        
    }
}

void RpiDrawObserver::clearInternalAndString() {
    _matrix.assign(_led_count, kBalckColor);
    std::fill(_led_string.channel[0].leds, _led_string.channel[0].leds + _led_count, kBalckColor);
    ws2811_render(&_led_string);
    ws2811_fini(&_led_string);

}
