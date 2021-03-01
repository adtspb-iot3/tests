#include <Arduino.h>
#include "timer.h"
#include "knopka.h"
#define TIME_SHORT 600
#define TIME_DOUBLE 500
// bool volatile button1 {};
bool flag{0};
const int PIN {D3};
//*************
int pin{PIN};

enum class Stats{
  NONE,
  SHORT_PRESS,
  LONG_PRESS,
  DOUBLE_PRESS
};
Stats volatile sost{};
//***********************
// Knopka knopka (PIN, &flag);
unsigned long volatile t1{};
unsigned long volatile t2{};
unsigned long volatile t3{};
unsigned long volatile t_o{};
//********************************
bool button_down{};
//***************************
bool getShort(){
  return t_o > millis();
}
//---------------------------
void push_button_down();
void ICACHE_RAM_ATTR push_button_up(){
  static unsigned long millis_prev_up;
  if (millis() - 200 > millis_prev_up)
  {
    t2 = millis_prev_up = millis();
    if(t2 - t1 >= TIME_SHORT) {
      sost = Stats::LONG_PRESS;
    }
     else {
      if( t3 > 0 )
        sost = Stats::SHORT_PRESS;
    }
  }
  attachInterrupt(digitalPinToInterrupt(pin), push_button_down, FALLING);
}
void ICACHE_RAM_ATTR push_button_down(){
  static unsigned long millis_prev;
  if (millis() - 200 > millis_prev){
    millis_prev = t1 = millis();
    if( t1 - t3 < TIME_DOUBLE){
      sost = Stats::DOUBLE_PRESS;
      t2 = t3 = 0;
    } else t3 = t1;
  }
  attachInterrupt(digitalPinToInterrupt(pin), push_button_up, RISING);
};
//******************* 
void setup(){
  Serial.begin(115200);
  pinMode(PIN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), push_button_down, FALLING);
}
 
void loop() {
  // Serial.println(digitalRead(PIN));
  if(sost != Stats::NONE){
    Serial.println( static_cast<int>(sost));
    sost = Stats::NONE;
  }
}
 

