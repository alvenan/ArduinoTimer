#include <Arduino.h>

#define INIT_TEST 4 // gpio20
#define FINI_TIMER 2 // gpio21

volatile bool isTimerRunning = false;

int count = 0;
long int time_value = 0;

void finishTimer() {
  isTimerRunning = !isTimerRunning;
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(INIT_TEST, OUTPUT);
  pinMode(FINI_TIMER, INPUT);

  attachInterrupt(digitalPinToInterrupt(FINI_TIMER), finishTimer, RISING);

  digitalWrite(INIT_TEST, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(INIT_TEST, HIGH);
  if(count==0)
    Serial.println("Timer set and waiting to begin. ");

  while (!isTimerRunning); // 1st trigger
  time_value = micros();

  digitalWrite(INIT_TEST, LOW);
  digitalWrite(LED_BUILTIN, HIGH);

  while(isTimerRunning);  // 2nd trigger
  time_value = micros() - time_value;
  Serial.println(String(count) + ", " + String(time_value));
  count+=1;
}