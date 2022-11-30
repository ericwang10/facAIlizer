#include "Angry.h"
#include "Mood.h"

class Angry: public Mood {
    public:
        static Angry* GetInstance() {
            static Angry mood_angry;
            return &mood_angry;
        }
        virtual void playSound() {
            system("afplay Angry_Sound.wav");
        }
};