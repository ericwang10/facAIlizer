#ifndef HAPPY_H
#define HAPPY_H

#include "Mood.h"

class Happy: public Mood {
    public:
        static Happy* GetInstance();
        virtual void playSound();
};

#endif