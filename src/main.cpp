#include <Arduino.h>
#include "timer.h"
#include "knopka.h"
// bool volatile button1 {};
bool flag{0};
const int PIN {14};
//*************
Knopka knopka (PIN, &flag);
//*******************
void setup(){
  Serial.begin(115200);
  // pinMode(PIN,INPUT_PULLUP);

}
 
void loop() {
if(flag) {
    int k = knopka.Whatsapp();
    Serial.println(k);
    flag = 0;
  }
  knopka.cycle();

}
 

