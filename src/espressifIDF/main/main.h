#ifndef MAIN_HEADER
#define MAIN_HEADER

// including libraries
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_attr.h"
#include "esp_log.h"


// pin assignments
#define DATA GPIO_NUM_4 // DATA LED pin
#define SYNC GPIO_NUM_16 // SYNC LED pin
#define ENABLE GPIO_NUM_23 // ENABLE button pin
#define SELECT GPIO_NUM_22 // SELECT button pin


#define DEBUG 1 // defining debug mode, 1 = slow down time, 0 = real time

#if DEBUG // conditional compilation for debug mode
#define FACTOR 1000 // slows down the waveform
#else
#define FACTOR 1 // waveform occurs in realtime
#endif

#define ONTIME 800 // defines the duration of the first pulse on-time in the DATA waveform - also known as "a" (see above)
#define TON(val) (ONTIME + ((val-1) * 50)) // used to define the duration of each pulse in the DATA waveform


// system parameters calculated above
const uint16_t offTime = 1200; // defines the time (in microseconds) of each pulse off-time in a DATA waveform cycle - also known as "b" (see above)
const uint16_t numPulses = 16; // defines the number of pulses - also known as "c" (see above)
const uint16_t idleTime = 6500; // defines the idle time between the end of the waveform and the start of the SYNC pulse - also known as "d" (see above)
const uint8_t tysncOn = 50; // defines the duration of the SYNC pulse
const uint8_t debounceDelay = 50; // debounce time in milliseconds used for button presses

uint8_t enableState = 0; // used to toggle the DATA LED on/off

int8_t selection = 1; // used to select between waveforms, selection = 1 represents normal waveform, selection = -1 represents alternate waveform

volatile unsigned long lastDebounceTime1 = 0; // Store last press time
volatile unsigned long lastDebounceTime2 = 0; // Store last press time


// function prototypes
void customDelay(uint32_t t); // custom delay function to take into account debug delay if activated
void dataPulse(uint16_t pulseCounter); // data pulse function
void syncPulse(void); // sync pulse function
void my_loop(void); // waveform control method


#endif