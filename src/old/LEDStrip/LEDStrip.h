/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LEDStrip.h
 * Author: yovany
 *
 * Created on January 24, 2018, 8:03 PM
 */

#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>

#include "../libs/clk.h"
#include "../libs/gpio.h"
#include "../libs/dma.h"
#include "../libs/pwm.h"
#include "../libs/version.h"

#include "../libs/ws2811.h"

#define ARRAY_SIZE(stuff)       (sizeof(stuff) / sizeof(stuff[0]))

// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// LEDStrip/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// LEDStrip/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)


class LEDStrip {
public:
    int width;
    int height;
    int led_count;
    ws2811_t ledstring;
    ws2811_led_t *matrix;
    ws2811_return_t ret;

    LEDStrip(int w = 8, int h = 8);
    LEDStrip(const LEDStrip& orig);
    virtual ~LEDStrip();
    
    bool ledDisplay();
    void turnOff(int idx);
    void turnOn(int idx, uint32_t color);
    void turnOn(int idx, uint8_t red, uint8_t green, uint8_t blue);
    void release();
    
    void matrix_render();

    void matrix_bottom();
    void matrix_raise();

private:

    void ledInit(int w = 8, int h = 8);
    void matrix_clear();
    
    
};

#endif /* LEDStrip_H */

