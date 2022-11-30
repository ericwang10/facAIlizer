#ifndef FEARFUL_H
#define FEARFUL_H

#include "Mood.h"

class Fearful: public Mood {
    public:
        static Fearful* GetInstance();
        virtual void playSound();
};

#endif