//Todo, add documentation here

#include "Mood.h"

//state class 
//virtual void Mood::playSound() = 0;
 



class Happy: public Mood {
    public:
        static Happy* GetInstance() {
            static Happy mood_happy;
            return &mood_happy;
        }
        virtual void playSound() {
            system("afplay Happy_Sound.mp3");
        }
};

class Neutral: public Mood {
    public:
        static Neutral* GetInstance() {
            static Neutral mood_neutral;
            return &mood_neutral;
        }
        virtual void playSound() {
            system("afplay Neutral_Sound.wav");
        }
};

class Sad: public Mood {
    public:
        static Sad* GetInstance() {
            static Sad mood_sad;
            return &mood_sad;
        }
        virtual void playSound() {
            system("afplay Sad_Sound.wav");
        }
};

class Surprised: public Mood {
    public:
        static Surprised* GetInstance() {
            static Surprised mood_surprised;
            return &mood_surprised;
        }
        virtual void playSound() {
            system("afplay Surprised_Sound.wav");
        }
};


class MoodController {
    Mood* moodState;
    public:
        MoodController() {
            moodState = nullptr;
        }
        void run(std::string emotion) {
            if (emotion == "Angry") {
                moodState = Angry::GetInstance();
                moodState->playSound();
            } else if (emotion == "Fearful") {
                moodState = Fearful::GetInstance();
                moodState->playSound();
            } else if (emotion == "Happy") {
                moodState = Happy::GetInstance();
                moodState->playSound();
            } else if (emotion == "Neutral") {
                moodState = Neutral::GetInstance();
                moodState->playSound();
            } else if (emotion == "Sad") {
                moodState = Sad::GetInstance();
                moodState->playSound();
            } else if (emotion == "Surprised") {
                moodState = Surprised::GetInstance();
                moodState->playSound();
            }
            
        }
};
