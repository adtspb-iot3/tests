#include <Arduino.h>
#include "timer.h"
#include "knopka.h"
#define TIME_SHORT 600
#define TIME_DOUBLE 500
#include <WiFi.h>
extern "C" {
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <EspMQTTClient.h>
/*
Датчик движения
Кнопка 17
Датчик освещённости i2c: SDA (GPIO 21), SCL (GPIO 22)
Индикаторный светодиод 15
Шим для LED светильника 16
*/
EspMQTTClient client(
  "adtspb-iot3",
  "iot3-620",
  "10.152.32.101",  // MQTT Broker server ip
  "",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "ARTEM",      // Client name that uniquely identify your device
  1883
);

const String test ="artem";



void onConnectionEstablished(){
 client.publish("iot3/mine",test);

}




const int TIMER_DOUBLE_PRESS {400};
bool flag{0};
const int PIN {15};//{D3};
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
  Serial.println();
  Serial.println();
  pinMode(PIN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), push_button_down, FALLING);
         
}
//*************************
Timer timer(TIMER_DOUBLE_PRESS);
unsigned long time_double{};
//*************************

unsigned long previousMillis {};
const long interval {5000};        
void loop() {
client.loop();
  // if(sost != Stats::NONE){//41
  //   switch(sost){
  //     case Stats::NONE:break; 
  //     case Stats::SHORT_PRESS: 
  //       if(time_double == 0)
  //         time_double = millis() + TIMER_DOUBLE_PRESS;
  //     break;
  //     case Stats::LONG_PRESS: Serial.println("Long");break;
  //     case Stats::DOUBLE_PRESS: 
  //       Serial.println("Double");
  //       time_double = 0;
  //     break;
  //   }
  //   sost = Stats::NONE;
  // }
  // if(time_double && (time_double < millis())){                                                                                                                                                                                                                                                                                  
  //   Serial.println("Short");
  //   time_double = 0;
  // }
}
 

