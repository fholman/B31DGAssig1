#include "main.h"

/**
 *
 * @author Fraser Holman
 * @date 27/02/2025
 *
 * @brief B31DG Assignment 1 - Part 1 Arduino Code
 *
 *
 * System creates a unique waveform that can be viewed in real time on an oscilloscope or visually from the LEDs when slowed down
 * 
 * Two interrupt buttons are implemented, the enable button activates and deactivates the DATA pulse and the select button changes the behaviour of the waveform
 *
 * The alternate waveform for this system is a reversed form of the DATA waveform starting at the widest pulse rather than the shortest
 *
 * By setting DEBUG to 1 this will slow down the waveform to be seen from the LED output
 * Setting DEBUG to 0 will show the waveform in real time which can be viewed on an oscilloscope
 *
 * Calculated System Parameters from the specification to define the nature of the waveform
 *
 * ## SYSTEM PARAMETERS - HOLMAN
 *  - ## PULSE TIMING
 *    - a = H - 8 x 100 = 800us = 0.8
 *    - b = O - 12 x 100 = 1200us = 1.2ms
 *    - c = L - 12 + 4 = 16
 *    - d = M - 13 x 500 = 6500us = 6.5ms
 *  - ## ALTERNATE BEHAVIOUR CALCULATION
 *    - alternate behaviour = A - 1 % 4 + 1 = 2
 *  - ## PULSE WIDTH FORMULA
 *    - TON(pulseCounter) = a + ((pulseCounter-1) x 50) = 800 + ((pulseCounter-1) x 50) for 2 <= pulseCounter <= 16 (c)
 *
*/


/**
 *
 * Method to handle enable button interrupt
 *
 */
void IRAM_ATTR enableClick(void *arg) {
    unsigned long currentTime = esp_timer_get_time(); // keeps track of number of milliseconds that have passed 

    // ignore interrupts that happen within debounceDelay
    if (currentTime - lastDebounceTime1 > debounceDelay) {
        enableState = enableState ? 0 : 1; // sets enableState to either 0 or 1 to toggle the DATA signal on/off
        lastDebounceTime1 = currentTime;  // Update last debounce time
    }
}  

/**
 *
 * Method to handle select button interrupt
 *
 */
void IRAM_ATTR selectClick(void *arg) {
    unsigned long currentTime = esp_timer_get_time(); // keeps track of number of milliseconds that have passed 

    // ignore interrupts that happen within debounceDelay
    if (currentTime - lastDebounceTime2 > debounceDelay) {
        selection *= - 1; // changes selection to either -1 or 1 to be used to either increment or decrement pulse counter in main loop
        lastDebounceTime2 = currentTime;  // Update last debounce time
    }
}

/**
 *
 * Initial function that is executed on system start
 * Contains setup code for GPIO pins
 *
 */
void app_main(void)
{
    // configure the ENABLE button to toggle DATA signal on/off
    gpio_set_direction(ENABLE,GPIO_MODE_INPUT);
    gpio_set_pull_mode(ENABLE,GPIO_PULLUP_ONLY); // enable pullup resistor for button
    gpio_set_intr_type(ENABLE, GPIO_INTR_NEGEDGE); // trigger interrupt on falling edge of button press

    // configure the SELECT button to change waveform behaviours
    gpio_set_direction(SELECT,GPIO_MODE_INPUT);
    gpio_set_pull_mode(SELECT,GPIO_PULLUP_ONLY); // enable pullup resistor for button
    gpio_set_intr_type(SELECT, GPIO_INTR_NEGEDGE); // trigger interrupt on falling edge of button press

    gpio_set_direction(DATA,GPIO_MODE_OUTPUT); // configure the DATA signal 
    gpio_set_direction(SYNC,GPIO_MODE_OUTPUT); // configure the SYNC signal

    // install ISR
    gpio_install_isr_service(ESP_INTR_FLAG_IRAM);

    // attach interrupts to the ENABLE and SELECT buttons
    gpio_isr_handler_add(ENABLE, enableClick, (void *)ENABLE);
    gpio_isr_handler_add(SELECT, selectClick, (void *)SELECT);

    my_loop(); // starts loop for data waveform control
}

/**
 *
 * Method to create a custom delay
 * The delay will be multiplied by FACTOR if in DEBUG mode this will be equal to 1000 and then 1 otherwise
 *
 * @param t desired delay (in microseconds)
 * 
 */
void customDelay(uint32_t t) {
    esp_rom_delay_us(t * FACTOR);
}

/**
 *
 * Method to generate one DATA pulse
 *
 * @param pulseCounter current pulse number
 * 
 */
void dataPulse(uint16_t pulseCounter) {
    // DATA pulse
    gpio_set_level(DATA, enableState); // turn LED high only if DATA has been enabled by a button interrupt
    customDelay(TON(pulseCounter)); // pulse width changes depending on pulse number
    gpio_set_level(DATA, 0);
    customDelay(offTime); // pulse off-time
}

/**
 *
 * Method to pulse the SYNC signal
 *
 */
void syncPulse() {
    gpio_set_level(SYNC, 1);
    customDelay(tysncOn); // SYNC pulse on-time (50us real time)
    gpio_set_level(SYNC, 0);
}

/**
 *
 * Loop contains logic to control the DATA and SYNC pulses
 *
 */
void my_loop() {
    while (true) {
        uint16_t pulseCounter; // counter to keep track of number of pulses

        syncPulse(); // SYNC pulse activated at beginning of waveform

        // selection = 1 means normal waveform
        // selection = -1 means alternate waveform
        // if normal waveform start pulseCOunter at 1
        // if alternate waveform start pulseCounter at the numPulses (in this case 16) 
        // if alternate waveform has been activated for loop will decrement rather than increment using the value of selection
        // for loop test case tests for both coniditions whether the pulseCounter has reached 1 or numPulses
        for (pulseCounter = (selection == 1 ? 1 : numPulses); pulseCounter > 0 && pulseCounter <= numPulses; pulseCounter+=selection) {
            #if DEBUG
                ESP_LOGI("Pulse Counter", "%d", pulseCounter);// monitor current pulse using serial monitor only if using debug mode
            #endif

            dataPulse(pulseCounter); // DATA pulse activated for each pulse
        }

        customDelay(idleTime); // idle time between last pulse off-time and SYNC pulse
    }
}