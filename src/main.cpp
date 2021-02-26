#include <Arduino.h>
#include "timer.h"
#include "knopka.h"
// bool volatile button1 {};
bool flag{0};
const int PIN {14};
//*************
int pin{PIN};

enum Stats{
  SHORT_PRESS,
  LONG_PRESS,
  DOUBLE_PRESS
};
Stats sost;
//***********************
// Knopka knopka (PIN, &flag);
  long int volatile t1{ };
   long int volatile t2{ };
   long int volatile t3{ };
   int volatile t_o{1200};
//********************************
   bool button_down{};
//***************************
void push_button_down();
void push_button_up(){
     static unsigned long millis_prev1;
    if (millis() - 200 > millis_prev1)
    {
          millis_prev1 = millis();
          t2 = millis();
            if(t2 - t1>=t_o)
            {
            sost=LONG_PRESS;
            t3=t1;
            Serial.println( sost);
            }
   else if(t2-t1<t_o)
   {
       sost=SHORT_PRESS;
       Serial.println( sost);
   }
    }
         attachInterrupt(digitalPinToInterrupt(pin), push_button_down, FALLING);
    
};
void push_button_down(){
        static unsigned long millis_prev;
    if (millis() - 200 > millis_prev){
        t1 = millis();
        // if(t1-t3>1000)
        button_down=true;
        millis_prev = millis();
    }
        attachInterrupt(digitalPinToInterrupt(pin), push_button_up, RISING);
    
};
//*******************
void setup(){
  Serial.begin(115200);
  pinMode(PIN,INPUT_PULLUP);

}
 
void loop() {

//Serial.println(digitalRead(PIN));
}
 

