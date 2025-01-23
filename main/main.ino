// HOLMAN
// H - 8 x 100 = 800us
// O - 12 x 100 = 1200us = 1.2ms
// L - 12 + 4 = 16
// M - 13 x 500 = 6500us = 6.5ms
// A - 1 % 4 + 1 = 2

#define LED1 G13
#define LED2 G26

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED1, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  delay(1000);
}
