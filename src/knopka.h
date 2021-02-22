#ifndef KNOPKA_H
#define KNOPKA_H
#include <Arduino.h>
#include "timer.h"

void push_button();
   
  enum Type_System {
    FREE,
    FIRST_PRESS,
    SECOND_PRESS
  };
 enum Type_Button {
    SHOT_PRESS,
    LONG_PRESS,
    DOUBLE_PRESS
  };
class Knopka :public Timer
{
    int pin;
    bool* flag ;
    Type_Button sost;
    Type_System sost_sys{FREE};
  public:
    Knopka(int p, bool* fl): Timer(10), pin(p),flag(fl) {
      pinMode(pin,INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(pin), push_button, RISING);
  }
 int Whatsapp(){
    return(static_cast<int>(sost));
  }
    void cycle();
   
    
};
#endif 