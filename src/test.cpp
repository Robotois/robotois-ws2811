#include <cstdlib>
#include <stdint.h>
#include <stdio.h>
#include <iostream>

// #include "./robotois-ws2811.h"
#include "LEDStrip/LEDStrip.h"


void runTest();
static void setup_handlers(void);
static void ctrl_c_handler(int signum);

static uint8_t running = 1;

int main(int argc, char *argv[])
{
    runTest();
    return 0;
}

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
    printf("Here!!\n");
    LEDStrip ledStrip;
    // ledStrip.turnOn(0, 0x00200000):
    // setup_handlers();
  while (running)
  {
//      printf("Running\n");
      ledStrip.matrix_raise();
      ledStrip.matrix_bottom();
      ledStrip.matrix_render();

      if (!ledStrip.ledDisplay()){
          break;
      }

      // 15 frames /sec
      usleep(1000000 / 15);
  }
  ledStrip.release();

  printf ("\n");
}
