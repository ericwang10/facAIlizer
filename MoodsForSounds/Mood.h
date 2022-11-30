#ifndef MOOD_H
#define MOOD_H


#include<iostream>
#include<thread>
 

#include "Angry.h"
#include "Fearful.h"
#include "Happy.h"
#include "Neutral.h"
#include "Sad.h"
#include "Surprised.h"



class Mood {
    public:
        virtual void playSound();
};


#endif