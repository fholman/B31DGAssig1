// HOLMAN
// a  H - 8 x 100 = 800us = 0.8
// b  O - 12 x 100 = 1200us = 1.2ms
// c  L - 12 + 4 = 16
// d  M - 13 x 500 = 6500us = 6.5ms
// A - 1 % 4 + 1 = 2

#define LED1 13
#define LED2 26
#define BUTTON1 23
#define BUTTON2 2

const bool debug = true;

const float a = 800;
const uint16_t b = 1200;
const uint16_t numPulses = 16;
const uint16_t d = 6500;
const uint8_t tysncOn = 50;

volatile byte button1State = LOW;
bool button2State = true;

bool start = true;

uint16_t n = 0;

volatile unsigned long lastDebounceTime1 = 0; // Store last press time
volatile unsigned long lastDebounceTime2 = 0; // Store last press time
const uint8_t debounceDelay = 50;     // Debounce time in milliseconds

void IRAM_ATTR button1Click() {
  unsigned long currentTime = millis();

  if (currentTime - lastDebounceTime1 > debounceDelay) {
    button1State = !button1State;
    lastDebounceTime1 = currentTime; // Update last debounce time
  }
}

void IRAM_ATTR button2Click() {
  unsigned long currentTime = millis();
  
  // Ignore interrupts that happen within debounceDelay
  if (currentTime - lastDebounceTime2 > debounceDelay) {
    button2State = !button2State;
    lastDebounceTime2 = currentTime; // Update last debounce time
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON1), button1Click, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON2), button2Click, RISING);
}

void loop() {

  if (!button2State) n--;

  if (n == numPulses || n == 0) 
  {
    if (!start) newDelay(d);

    start = false;

    digitalWrite(LED2, HIGH);
    newDelay(tysncOn);
    digitalWrite(LED2, LOW);

    n = button2State ? 0 : numPulses;
  }

  if (button2State) n++;

  Serial.println(n);

  digitalWrite(LED1, button1State);
  newDelay(newTime(n));
  digitalWrite(LED1, LOW);
  newDelay(b);

}

float newTime(uint16_t val) {
  return val<2 ? a : a + ((val-1) * 50);
}

void newDelay(uint32_t t) {
  if (debug) 
  {
    delayMicroseconds(t * 1000);
  }
  else 
  {
    delayMicroseconds(t);
  }
}
