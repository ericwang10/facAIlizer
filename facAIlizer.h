// facAIlizer.h : Include file for standard system include files,
// or project specific include files.

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
