/** 
   @brief facializer.h header file to support facializer.cpp
 * @author Team 19
 * @date 2022-11-28
*/

#ifndef FACAILIZER_H
#define FACAILIZER_H

#include <iostream>

#include <boost/algorithm/string.hpp>
#include <fdeep/fdeep.hpp>

#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

//#include "Mood.cpp"

class facAIlizer {

public:
    void detectAndDisplay(cv::Mat frame);
    

private:



};


#endif

