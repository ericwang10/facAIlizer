#ifndef SAD_H
#define SAD_H

#include "Mood.h"

class Sad: public Mood {
    public:
        static Sad* GetInstance();
        virtual void playSound();
};

#endif