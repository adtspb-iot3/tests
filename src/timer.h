#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
class Timer
{
  unsigned long t{ 0 };
  unsigned long dT{ 50 }; //время задержки
public:
  Timer() {}
  Timer(unsigned long dt):dT(dt) {}
  bool getTimer() { return t < millis(); }
  void setTimer(unsigned long dt = 0) {t = millis() + (dt == 0 ? dT : dt);}
  void setDt(unsigned long dt) { dT = dt; }
  void clearTimer(){t = 0;}
};
#endif