#ifndef ANGRY_H
#define ANGRY_H

#include "Mood.h"

class Angry: public Mood {
    public:
        static Angry* GetInstance(){};
        virtual void playSound(){};
};

#endif