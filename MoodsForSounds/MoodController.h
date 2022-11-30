
#ifndef MOODCONTROLLER_H
#define MOODCONTROLLER_H


#include "Mood.h"


class MoodController {
    Mood* moodState;
    public:
        MoodController();
        void run(std::string emotion);
};

#endif