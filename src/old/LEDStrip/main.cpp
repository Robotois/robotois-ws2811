/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yovany
 *
 * Created on January 24, 2018, 7:58 PM
 */

#include <cstdlib>
#include <thread>
#include <chrono>

#include "LEDStrip.h"

void runTest();
static void setup_handlers(void);
static void ctrl_c_handler(int signum);
void matrix_raise(LEDStrip *ledStrip);
void matrix_bottom(LEDStrip *ledStrip);

static uint8_t running = 1;

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
//    printf("Hello!!!\n");
//    LEDStrip ledStrip;
//    ledStrip.turnOn(0, (uint32_t)0x00200000);
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
//  setup_handlers();
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
