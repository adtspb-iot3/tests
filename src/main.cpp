#include <Arduino.h>
#include "timer.h"
#include "knopka.h"
#define TIME_SHORT 600
#define TIME_DOUBLE 500

const int TIMER_DOUBLE_PRESS {400};
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
unsigned long volatile t1{};
unsigned long volatile t2{};
unsigned long volatile t3{};
unsigned long volatile t_o{};
//********************************
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
//********************************
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
//*************************
Timer timer(TIMER_DOUBLE_PRESS);
unsigned long time_double{};
//*************************
void loop() {
  if(sost != Stats::NONE){//41
    switch(sost){
      case Stats::NONE:break; 
      case Stats::SHORT_PRESS: 
        if(time_double == 0){
          time_double = millis() + TIMER_DOUBLE_PRESS;
        } 
      break;
      case Stats::LONG_PRESS: Serial.println("Long");break;
      case Stats::DOUBLE_PRESS: 
        Serial.println("Double");
        time_double = 0;
      break;
    }
    sost = Stats::NONE;
  }
  if(time_double && (time_double < millis())){
    Serial.println("Short");
    time_double = 0;
  }
}
 

