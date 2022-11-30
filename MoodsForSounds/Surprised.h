#ifndef SURPRISED_H
#define SURPRISED_H

#include "Mood.h"

class Surprised: public Mood {
    public:
        static Surprised* GetInstance();
        virtual void playSound();
};

#endif