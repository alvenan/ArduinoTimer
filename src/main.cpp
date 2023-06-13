#include <Arduino.h>

#define START_BTN 3 
#define INIT_TEST 4 // gpio20
#define FINI_TIMER 2 // gpio21

#define NATIVE_OFFSET 199846
#define JNI_OFFSET 200509

#define N_TESTS 10

volatile bool isTesting = false;
volatile bool isTimerRunning= false;

long int time_value = 0;
char test_method = '0';

void startBtnPressed() {
  isTesting = true;
}

void finishTimer() {
  isTimerRunning = !isTimerRunning;
}

void setup() {
  Serial.begin(115200);

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
    for(int i=0; i<N_TESTS; i++){
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(INIT_TEST, HIGH);
        if(i==0)
          Serial.println("Timer set and waiting to begin. ");

        while (true)
          if(isTimerRunning){
            time_value = micros();
            break;
          }

        while (true)
          if(!isTimerRunning){
            switch(test_method) {
              case 's':
                time_value = micros() - time_value - NATIVE_OFFSET;
                Serial.println(String(i) + ", " + String(time_value/1000));
              break;
              case 'b':
                time_value = micros() - time_value - JNI_OFFSET; 
                Serial.println(String(i) + ", " + String(time_value/1000));
              break;
              default:
                time_value = micros() - time_value;
                Serial.println(String(i) + ", " + String(time_value));
            }
            break;
          }

        digitalWrite(INIT_TEST, LOW);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
    }
    isTesting = false;
    test_method = '0';
  } else {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if(Serial.available()) {
      test_method = Serial.read();
      if((test_method == 's')||(test_method == 'b')||(test_method == 'n'))
        isTesting = true;
    }
    delay(1000);
  }
}