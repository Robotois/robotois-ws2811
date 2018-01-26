/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WS2812.cpp
 * Author: yovany
 * 
 * Created on January 24, 2018, 8:03 PM
 */

#include "WS2812.h"


WS2812::WS2812() {
    width = WIDTH;
    height = HEIGHT;
    led_count = LED_COUNT;
    clear_on_exit = 0;
    ledstringInit();
    ledData = (ws2811_led_t *)malloc(sizeof(ws2811_led_t) * width * height);
    
}

WS2812::WS2812(const WS2812& orig) {
}

WS2812::~WS2812() {
}

void WS2812::setLedColor(uint32_t color) {
    ledData[0] = color;
    ledDataRender();
    ledsRender();
}


void WS2812::ledstringInit() {
  ledstring.freq = TARGET_FREQ;
  ledstring.dmanum = DMA;

  ledstring.channel[0].gpionum = GPIO_PIN;
  ledstring.channel[0].invert = 0;
  ledstring.channel[0].count = LED_COUNT;
  ledstring.channel[0].brightness = 255;
  ledstring.channel[0].strip_type = STRIP_TYPE;

  ledstring.channel[1].gpionum = 0;
  ledstring.channel[1].invert = 0;
  ledstring.channel[1].count = 0;
  ledstring.channel[1].brightness = 0;
  
    if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
    {
        fprintf(stderr, "[WS2812 Init Error] => %s\n", ws2811_get_return_t_str(ret));
    }
  
}

void WS2812::ledsClear(){
    ledDataClear();
    ledDataRender();
    ledsRender();
}

void WS2812::ledsRender() {
    if((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS) {
        fprintf(stderr, "[WS2812 Error] => %s\n", ws2811_get_return_t_str(ret));
    }    
}

void WS2812::ledDataClear() {
    for (int y = 0; y < (height ); y++)
    {
        for (int x = 0; x < width; x++)
        {
            ledData[y * width + x] = 0;
        }
    }    
}

void WS2812::ledDataRender() {
    int ledIndex = 0;
    for (int y = 0; y < (height ); y++)
    {
        for (int x = 0; x < width; x++)
        {
            ledIndex = y * width + x;
            ledstring.channel[0].leds[ledIndex] = ledData[ledIndex];
        }
    }    
}

void WS2812::release() {
    ledsClear();
    ws2811_fini(&ledstring);
}
