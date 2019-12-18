#ifndef CLOCKMOVER_H
#define CLOCKMOVER_H

#include "Arduino.h"

class ClockMover {
  public:
    void setup(void);
    void clear(void);
    void setTime(int hour, int minute);
    String getTime(void);
    void executeCorrectTime(void);
    void oneStep(int minuts);
    void executeGoCrazy(void);
    void executeMoveForward(void);
    void executeMoveBackward(void);

  private:
    int sd = 100;

    int timeHour = 0;
    int timeMinute = 0;

    void stepMinutes(int minuts);
    void addTime(int minutes);

    int accelerateStep(void);
};

#endif
