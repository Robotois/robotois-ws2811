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


#include "WS2812.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    WS2812 led;
    
    led.setLedColor(0x00100000); 
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    led.setLedColor(0x00002000); 
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    led.setLedColor(0x00000020); 
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    led.ledsClear();
    
    return 0;
}

