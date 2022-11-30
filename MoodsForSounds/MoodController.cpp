
#include "Mood.h"
#include "Angry.h"
#include "Fearful.h"
#include "Happy.h"
#include "Neutral.h"
#include "Sad.h"
#include "Surprised.h"


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
