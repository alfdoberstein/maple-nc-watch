#ifndef CLOCKMOVER_H
#define CLOCKMOVER_H

class ClockMover {
  public:
    void setup(void);
    void clear(void);
    bool executeCorrectTime(void);
    bool executeGoViral(void);
    bool executeMoveForward(void);
    bool executeMoveBackward(void);

  private:
    int sd = 100;
    
    int accelerateStep(void);
};

#endif
