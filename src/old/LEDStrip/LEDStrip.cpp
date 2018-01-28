/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LEDStrip.cpp
 * Author: yovany
 * 
 * Created on January 24, 2018, 8:03 PM
 */

#include "LEDStrip.h"
#include <iostream>
#include <stdio.h>

LEDStrip::LEDStrip(int w, int h) {
    std::cout<<"W: "<<w<<" H: "<<h<<'\n';
    ledInit(w, h);
}

LEDStrip::LEDStrip(const LEDStrip& orig) {
}

LEDStrip::~LEDStrip() {
}

void LEDStrip::ledInit(int w, int h) {
  width = w;
  height = h;
  led_count = w*h;
  ledstring.freq = TARGET_FREQ;
  ledstring.dmanum = DMA;
  ledstring.channel[0].gpionum = GPIO_PIN;
  ledstring.channel[0].count = led_count;
  ledstring.channel[0].invert = 0;
  ledstring.channel[0].brightness = 255;
  ledstring.channel[0].strip_type = STRIP_TYPE;

  ledstring.channel[1].gpionum = 0;
  ledstring.channel[1].count = 0;
  ledstring.channel[1].invert = 0;
  ledstring.channel[1].brightness = 0;
  matrix = (ws2811_led_t *)malloc(sizeof(ws2811_led_t) * width * height);
  
  if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS)
  {
      fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
  }
}

void LEDStrip::matrix_render(void)
{
    int x, y;

    for (x = 0; x < width; x++)
    {
        for (y = 0; y < height; y++)
        {
            ledstring.channel[0].leds[(y * width) + x] = matrix[y * width + x];
        }
    }
}

void LEDStrip::matrix_clear(void)
{
    int x, y;

    for (y = 0; y < (height ); y++)
    {
        for (x = 0; x < width; x++)
        {
            matrix[y * width + x] = 0;
        }
    }
}

bool LEDStrip::ledDisplay() {
  if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS)
  {
      printf("ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
      fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
      return false;
  }
  return true;
}

void LEDStrip::turnOff(int idx) {
  matrix[idx] = (ws2811_led_t) 0;
  matrix_render();
  ledDisplay();
}

void LEDStrip::turnOn(int idx, uint32_t color) {
  matrix[idx] = (ws2811_led_t) color;
  matrix_render();
  printf("Here!!!\n");
  ledDisplay();
}

void LEDStrip::turnOn(int idx, uint8_t red, uint8_t green, uint8_t blue) {
  uint32_t color;
  color = (0x00FFFFFF) & ((red) << 16 | (green) << 8 | (blue));
  turnOn(0, (uint32_t)0x00200000);
//  turnOn(idx, color);
}

void LEDStrip::release() {
  matrix_clear();
  matrix_render();
  ledDisplay();
  ws2811_fini(&ledstring);
}

int dotspos[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
ws2811_led_t dotcolors[] =
{
    0x00200000,  // red
    0x00201000,  // orange
    0x00202000,  // yellow
    0x00002000,  // green
    0x00002020,  // lightblue
    0x00000020,  // blue
    0x00100010,  // purple
    0x00200010,  // pink
};

ws2811_led_t dotcolors_rgbw[] =
{
    0x00200000,  // red
    0x10200000,  // red + W
    0x00002000,  // green
    0x10002000,  // green + W
    0x00000020,  // blue
    0x10000020,  // blue + W
    0x00101010,  // white
    0x10101010,  // white + W

};

void LEDStrip::matrix_bottom(void)
{
    int i;

    for (i = 0; i < (int)(ARRAY_SIZE(dotspos)); i++)
    {
        dotspos[i]++;
        if (dotspos[i] > (width - 1))
        {
            dotspos[i] = 0;
        }

        if (ledstring.channel[0].strip_type == SK6812_STRIP_RGBW) {
            matrix[dotspos[i] + (height - 1) * width] = dotcolors_rgbw[i];
        } else {
            matrix[dotspos[i] + (height - 1) * width] = dotcolors[i];
        }
    }
}

void LEDStrip::matrix_raise(void)
{
    int x, y;

    for (y = 0; y < (height - 1); y++)
    {
        for (x = 0; x < width; x++)
        {
            // This is for the 8x8 Pimoroni Unicorn-HAT where the LEDS in subsequent
            // rows are arranged in opposite directions
            matrix[y * width + x] = matrix[(y + 1)*width + width - x - 1];
        }
    }
}