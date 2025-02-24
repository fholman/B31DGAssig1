#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_attr.h"

//idf.py fullclean
//idf.py build

// HOLMAN
// a  H - 8 x 100 = 800us = 0.8
// b  O - 12 x 100 = 1200us = 1.2ms
// c  L - 12 + 4 = 16
// d  M - 13 x 500 = 6500us = 6.5ms
// A - 1 % 4 + 1 = 2

#define LED1 GPIO_NUM_4
#define LED2 GPIO_NUM_16
#define BUTTON1 GPIO_NUM_23
#define BUTTON2 GPIO_NUM_22

#define DEBUG 1

#ifdef DEBUG
#define FACTOR 1000
#else
#define FACTOR 1
#endif

const float a = 800;
const uint16_t b = 1200;
const uint16_t numPulses = 16;
const uint16_t d = 6500;
const uint8_t tysncOn = 50;

uint8_t button1State = 0;
bool button2State = true;

bool start = true;

uint16_t n = 0;

volatile unsigned long lastDebounceTime1 = 0; // Store last press time
volatile unsigned long lastDebounceTime2 = 0; // Store last press time
volatile uint8_t debounceDelay = 50;

static void IRAM_ATTR button1_isr_handler(void *arg) {
    unsigned long currentTime = esp_timer_get_time() / 1000;  // Convert to ms

    printf("Button 1 pressed \n");

    // Debounce check
    if (currentTime - lastDebounceTime1 > debounceDelay) {
        if (button1State) {
            button1State = 0;
        }
        else {
            button1State = 1;
        }
        lastDebounceTime2 = currentTime;  // Update debounce time
    }
}

void IRAM_ATTR button2_isr_handler(void *arg) {
    unsigned long currentTime = esp_timer_get_time() / 1000;  // Convert to ms

    ESP_LOGI("MY_TAG", "This is an info message!");

    // Debounce check
    if (currentTime - lastDebounceTime2 > debounceDelay) {
        button2State = !button2State;  // Toggle button state
        lastDebounceTime2 = currentTime;  // Update debounce time
    }
}

float newTime(uint16_t val) {
    return val<2 ? a : a + ((val-1) * 50);
}

void my_loop() {
    while (true) {
        if (!button2State) n--;

        ESP_LOGI("MY_TAG", "This is an info message!");

        if (n == numPulses || n == 0) 
        {
            if (!start) esp_rom_delay_us(d * FACTOR);

            start = false;

            gpio_set_level(LED1, 1);
            esp_rom_delay_us(tysncOn * FACTOR);
            gpio_set_level(LED1, 0);

            n = button2State ? 0 : numPulses;
        }

        if (button2State) n++;

        gpio_set_level(LED2, button1State);
        esp_rom_delay_us(newTime(n) * FACTOR);
        gpio_set_level(LED2, 0);
        esp_rom_delay_us(b * FACTOR);
    }
}


void app_main(void)
{
    gpio_set_direction(BUTTON1,GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON1,GPIO_PULLUP_ONLY);
    gpio_set_intr_type(BUTTON1, GPIO_INTR_POSEDGE);

    gpio_set_direction(BUTTON2,GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON2,GPIO_PULLUP_ONLY);

    gpio_set_direction(LED1,GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2,GPIO_MODE_OUTPUT);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON1, button1_isr_handler, NULL);
    gpio_isr_handler_add(BUTTON2, button2_isr_handler, (void *)BUTTON2);

    my_loop();
}