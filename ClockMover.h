#ifndef CLOCKMOVER_H
#define CLOCKMOVER_H

class ClockMover {
  public:
    void setup(void);
    void clear(void);
    void executeCorrectTime(void);
    void oneStep(void);
    void executeGoCrazy(void);
    void executeMoveForward(void);
    void executeMoveBackward(void);

  private:
    int sd = 100;

    int accelerateStep(void);
};

#endif
