#ifndef CLOCKMOVER_H
#define CLOCKMOVER_H

class ClockMover {
    public:
        void setup (void);
        bool executeCorrectTime(void);
        bool executeGoViral(void);
        bool executeMoveForward(void);
        bool executeMoveBackward(void);
};

#endif