#include <Arduino.h>

#define TIMER_READY 4 // gpio20
#define TRIGGER 2 // gpio21

volatile bool isTimerRunning = false;

int count = 0;
long int time_value = 0;

void finishTimer() {
  isTimerRunning = !isTimerRunning;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TIMER_READY, OUTPUT);
  pinMode(TRIGGER, INPUT);

  attachInterrupt(digitalPinToInterrupt(TRIGGER), finishTimer, RISING);

  digitalWrite(TIMER_READY, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(TIMER_READY, HIGH);
  if(count==0)
    Serial.println("Timer set and waiting to begin. ");

  while (!isTimerRunning); // 1st trigger
  time_value = micros();

  digitalWrite(TIMER_READY, LOW);
  digitalWrite(LED_BUILTIN, HIGH);

  while(isTimerRunning);  // 2nd trigger
  time_value = micros() - time_value;
  Serial.println(String(count) + ", " + String(time_value));
  count+=1;
}