/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WS2812.h
 * Author: yovany
 *
 * Created on January 24, 2018, 8:03 PM
 */

#ifndef WS2812_H
#define WS2812_H

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
#define DMA                     5
#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6811_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define WIDTH                   1
#define HEIGHT                  1
#define LED_COUNT               (WIDTH * HEIGHT)

class WS2812 {
public:
    WS2812();
    WS2812(const WS2812& orig);
    virtual ~WS2812();

    void ledsClear();
    void release();
    
    void setLedColor(uint32_t color);
    
private:
    int width;
    int height;
    int led_count;

    int clear_on_exit;
    ws2811_t ledstring;
    ws2811_led_t *ledData;
    ws2811_return_t ret;

    
    void ledstringInit();
    void ledDataClear();
    void ledDataRender();
    void ledsRender();
};

#endif /* WS2812_H */

