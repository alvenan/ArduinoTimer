#include <Arduino.h>

#define INPUT_PIN 3

bool timerState = false;
uint32_t task_time = 0;

void pin_ISR() {
  if(!timerState) {
    task_time = millis();
    Serial.println("Start Timer.");
    timerState = true;
  } else {
    task_time = millis() - task_time;
    Serial.print("Stop Timer in ");
    Serial.print(task_time);
    Serial.println("ms.");
    timerState = false;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(INPUT_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(INPUT_PIN), pin_ISR, RISING);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if(timerState)
    digitalWrite(LED_BUILTIN, HIGH);
  else {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(200);
  }

}