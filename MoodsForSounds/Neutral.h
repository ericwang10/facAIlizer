#ifndef NEUTRAL_H
#define NEUTRAL_H

#include "Mood.h"

class Neutral: public Mood {
    public:
        static Neutral* GetInstance();
        virtual void playSound();
};

#endif