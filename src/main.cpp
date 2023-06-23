#include <Arduino.h>

#define DEBUG

#define TIMER_READY 4 // gpio20
#define RESET 3 // gpio16
#define TRIGGER 2 // gpio21

volatile bool isTimerRunning = false;

int count = 0;
long unsigned int time_value = 0;

void finishTimer() {
  isTimerRunning = !isTimerRunning;
}

void resetTimer() {
  Serial.println("Timer set and waiting to begin. ");
  count = 0;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TIMER_READY, OUTPUT);
  pinMode(TRIGGER, INPUT);
  pinMode(RESET, INPUT);

  attachInterrupt(digitalPinToInterrupt(TRIGGER), finishTimer, RISING);
  attachInterrupt(digitalPinToInterrupt(RESET), resetTimer, RISING);

  digitalWrite(TIMER_READY, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  resetTimer();
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(TIMER_READY, HIGH);

  while (!isTimerRunning) // 1st trigger
  time_value = micros();

  digitalWrite(TIMER_READY, LOW);
  digitalWrite(LED_BUILTIN, HIGH);

  while(isTimerRunning);  // 2nd trigger
  time_value = micros() - time_value;
  Serial.println(String(count) + ", " + String(time_value));
  count+=1;
}