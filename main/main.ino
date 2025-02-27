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
 *    - TON(pulseCounter) = a + ((pulseCounter-1) x 50) = 800 + ((pulseCounter-1 x 50)) for 2 <= pulseCounter <= 16 (c)
 *
*/

// pin assignments
#define DATA 4 // DATA LED pin
#define SYNC 16 // SYNC LED pin
#define ENABLE 23 // enable button pin
#define SELECT 22 // select button pin


#define DEBUG 1 // defining debug mode, 1 = slow down time, 0 = real time

#if DEBUG // conditional compilation for debug mode
#define FACTOR 1000 // slows down the waveform
#else
#define FACTOR 1 // waveform occurs in real time
#endif

#define ONTIME 800 // defines the duration of the first pulse on-time in the DATA waveform - also known as "a" (see above)
#define TON(val) (ONTIME + ((val-1) * 50)) // used to define the duration of each pulse in the DATA waveform


// system parameters calculated above
const uint16_t offTime = 1200; // defines the time (in microseconds) of each pulse off-time in a DATA waveform cycle - also known as "b" (see above)
const uint16_t numPulses = 16; // defines the number of pulses - also known as "c" (see above)
const uint16_t idleTime = 6500; // defines the idle time between the end of the waveform and the start of the SYNC pulse - also known as "d" (see above)
const uint8_t tysncOn = 50; // defines the duration of the SYNC pulse
const uint8_t debounceDelay = 50; // debounce time in milliseconds used for button presses


volatile byte enableState = LOW; // used to toggle the DATA LED on/off

int8_t selection = 1; // used to select between waveforms, selection = 1 represents normal waveform, selection = -1 represents alternate waveform

// time variables to prevent debounce in the two buttons
volatile unsigned long lastDebounceTime1 = 0; // store last press time for enable button
volatile unsigned long lastDebounceTime2 = 0; // store last press time for select button


// function prototypes
void IRAM_ATTR enableClick(void); // enable button interrupt
void IRAM_ATTR selectClick(void); // select button interrupt
void dataPulse(uint16_t pulseCounter); // data pulse function
void syncPulse(void); // sync pulse function
void customDelay(uint32_t t); // custom delay function to take into account debug delay if activated


/**
 *
 * Setup method contains the system setup code
 *
 */
void setup() {
  #if DEBUG
    Serial.begin(9600); // only start serial if system is in debug mode
  #endif

  // pin setup for LEDs
  pinMode(DATA, OUTPUT); // DATA LED setup
  pinMode(SYNC, OUTPUT); // SYNC LED setup

  // pin setup for buttons with pullup resistors
  pinMode(ENABLE, INPUT_PULLUP); // enable button setup
  pinMode(SELECT, INPUT_PULLUP); // select button setup

  // attaching interrupt to the button pins
  attachInterrupt(digitalPinToInterrupt(ENABLE), enableClick, RISING); // interrupt on the rising edge for enable button
  attachInterrupt(digitalPinToInterrupt(SELECT), selectClick, RISING); // interrupt on the rising edge for select button
}

/**
 *
 * Loop contains logic to control the DATA and SYNC pulses
 *
 */
void loop() {
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
      Serial.println(pulseCounter); // monitor current pulse using serial monitor only if using debug mode
    #endif

    dataPulse(pulseCounter); // DATA pulse activated for each pulse
  }

  customDelay(idleTime); // idle time between last pulse off-time and SYNC pulse
}

/**
 *
 * Method to handle enable button interrupt
 *
 */
void IRAM_ATTR enableClick() {
  unsigned long currentTime = millis(); // keeps track of number of milliseconds that have passed 

  // ignore interrupts that happen within debounceDelay
  if (currentTime - lastDebounceTime1 > debounceDelay) {
    enableState = !enableState; // sets byte from LOW to HIGH or HIGH to LOW
    lastDebounceTime1 = currentTime; // Update last debounce time
  }
}

/**
 *
 * Method to handle select button interrupt
 *
 */
void IRAM_ATTR selectClick() {
  unsigned long currentTime = millis(); // keeps track of number of milliseconds that have passed 
  
  // ignore interrupts that happen within debounceDelay
  if (currentTime - lastDebounceTime2 > debounceDelay) {
    selection *= - 1; // changes selection to either -1 or 1 to be used to either increment or decrement pulse counter in main loop
    lastDebounceTime2 = currentTime; // Update last debounce time
  }
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
  digitalWrite(DATA, enableState); // turn LED high only if DATA has been enabled by a button interrupt
  customDelay(TON(pulseCounter)); // pulse width changes depending on pulse number
  digitalWrite(DATA, LOW);
  customDelay(offTime); // pulse off-time
}

/**
 *
 * Method to pulse the SYNC signal
 *
 */
void syncPulse() {
  digitalWrite(SYNC, HIGH);
  customDelay(tysncOn); // SYNC pulse on-time (50us real time)
  digitalWrite(SYNC, LOW);
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
  delayMicroseconds(t * FACTOR);
}