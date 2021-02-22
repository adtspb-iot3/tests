#include <Arduino.h>
#include "knopka.h"
bool volatile button1;

//**************************
void push_button(){
     static unsigned long millis_prev;
  if (millis() - 200 > millis_prev)
    button1 = 1;
   
  millis_prev = millis();
};
void Knopka::cycle() {
    switch(sost_sys){
    case FREE: 
        if(button1) { 
            setTimer(1200); 
            button1 = 0; 
            sost_sys = FIRST_PRESS; 
            Serial.println("FREE");
        } 
    break;
    case FIRST_PRESS: 
        if(getTimer()){
            Serial.println("FIRST_PRESS");
            if(digitalRead(pin))
            {
                Serial.println("LONG");
                sost=LONG_PRESS;
            }
            else {
                sost=SHOT_PRESS;
                Serial.println("short");
            }; 
            sost_sys = FREE;
            *flag = 1;
        } else if(button1) {
                sost_sys = FREE;
                Serial.println("Double");
                *flag=1;
                sost=DOUBLE_PRESS;
            }
            else Serial.println("ELSE");
     break;
    };
   


}
