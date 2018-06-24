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

#include "./libs/clk.h"
#include "./libs/gpio.h"
#include "./libs/dma.h"
#include "./libs/pwm.h"
#include "./libs/version.h"

#include "./libs/ws2811.h"

#ifndef ROBOTOIS_WS2811_H
#define ROBOTOIS_WS2811_H

#define ARRAY_SIZE(stuff)       (sizeof(stuff) / sizeof(stuff[0]))
// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN1                18
#define GPIO_PIN2                12
#define DMA                     10
// #define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

int width;
int height;
int led_count;

ws2811_t ledstring;
ws2811_led_t *matrix;
ws2811_return_t ret;

/**
 * Initializes the struct for the ledStrip and the data matrix
 * @param w Width of the data matrix
 * @param h Height of the data matrix, if height is 1 it will be like an array
 */
void ledStripInit(int w = 8, int h = 8, uint8_t brightness = 255, uint8_t pin = 1) {
  width = w;
  height = h;
  led_count = w*h;
  uint8_t ioPin;
  if(pin == 1) {
    ioPin = GPIO_PIN1;
  } else {
    ioPin = GPIO_PIN2;
  }
  ledstring.freq = TARGET_FREQ;
  ledstring.dmanum = DMA;
  ledstring.channel[0].gpionum = ioPin;
  ledstring.channel[0].count = led_count;
  ledstring.channel[0].invert = 0;
  ledstring.channel[0].brightness = brightness;
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

/**
 * Renders the data matrix to the ledstring configuration struct, this is a previous step
 * to the display
 */
void matrix_render(void)
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

/**
 * Clears the data matrix where the led colors are stored
 */
void matrix_clear(void)
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

/**
 * Display the current ledstring configuration.
 * @return Wether the render failed or not
 */
bool ledStripDisplay() {
  if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS)
  {
      fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
      return false;
  }
  return true;
}

/**
 * Clears the led
 * @param idx   index of the led to clear
 */
void turnOff(int idx) {
  matrix[idx] = 0;
  matrix_render();
  ledStripDisplay();
}

/**
 * Set the color of a Single LED in the ledStrip
 * @param idx   index of the led to change its color
 * @param color color in format of a uint32_t (2 Bytes per channel
 *  [W][R][G][B] => 0x00200000,  // red)
 */
void turnOn(int idx, ws2811_led_t color) {
  matrix[idx] = color;
  matrix_render();
  ledStripDisplay();
}

void turnOn(int idx, uint8_t red, uint8_t green, uint8_t blue) {
  uint32_t color = 0x00000000;
  color = (red << 16) | (green << 8) | (blue);
  // printf("Color: %x\n", color);
  turnOn(idx, color);
}

void allOn(uint8_t red, uint8_t green, uint8_t blue) {
  uint32_t color = 0x00000000;
  color = (red << 16) | (green << 8) | (blue);
  int x, y;

  for (y = 0; y < (height ); y++)
  {
      for (x = 0; x < width; x++)
      {
          matrix[y * width + x] = color;
      }
  }
  matrix_render();
  ledStripDisplay();
}

void allOff() {
  matrix_clear();
  matrix_render();
  ledStripDisplay();
}

/**
 * properly releases the ledStrip, clear the data matrix, render and finalizes the ws2811 library
 */
void ledStripRelease() {
  matrix_clear();
  matrix_render();
  ledStripDisplay();
  ws2811_fini(&ledstring);
}

/****
Variables and Functions for running the test
 ****/

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

void matrix_bottom(void)
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

void matrix_raise(void)
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

static uint8_t running = 1;
int clear_on_exit = 1;

static void ctrl_c_handler(int signum)
{
	(void)(signum);
    running = 0;
}

static void setup_handlers(void)
{
    struct sigaction sa;
    sa.sa_handler = ctrl_c_handler,
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

void runTest() {
  ledStripInit();
  setup_handlers();
  while (running)
  {
      matrix_raise();
      matrix_bottom();
      matrix_render();

      if (!ledStripDisplay()){
          break;
      }

      // 15 frames /sec
      usleep(1000000 / 15);
  }
  ledStripRelease();

  printf ("\n");
}
#endif
