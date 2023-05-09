#include <Arduino.h>

#define START_BTN 3 
#define INIT_TEST 4 // gpio20
#define FINI_TIMER 2 // gpio21

#define COMM_OFFSET 18
#define N_TESTS 5

volatile bool isTesting = false;
volatile bool isTimerRunning= false;

int time_value = 0;

void startBtnPressed() {
  isTesting = true;
}

void finishTimer() {
  isTimerRunning = false;
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(START_BTN, INPUT);
  pinMode(INIT_TEST, OUTPUT);
  pinMode(FINI_TIMER, INPUT);

  attachInterrupt(digitalPinToInterrupt(START_BTN), startBtnPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(FINI_TIMER), finishTimer, RISING);

  digitalWrite(INIT_TEST, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if(isTesting) {
    for(int i=0; i<=N_TESTS; i++){
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(INIT_TEST, HIGH);
        isTimerRunning = true;
        time_value = millis();

        if(i==0)
          // first pulse is to check operation
          Serial.println("Configurando Timer");

        while (true)
          if(!isTimerRunning){
            time_value = millis() - time_value - COMM_OFFSET;
            break;
          }
        if(i!=0)
          Serial.println(String(i) + ", " + String(time_value));

        digitalWrite(INIT_TEST, LOW);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
    }
    isTesting = false;
  } else {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(1000);
  }
}