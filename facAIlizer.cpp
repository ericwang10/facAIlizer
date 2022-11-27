// facAIlizer.cpp : Defines the entry point for the application.
//

#include "facAIlizer.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/opencv.hpp>

#include <iostream>
#include <fdeep/fdeep.hpp>



using namespace std;
using namespace cv;
void detectAndDisplay(Mat frame);
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
int main(int argc, const char** argv)
{
    //const auto model = fdeep::load_model("C:/Users/Pinkie/source/repos/facAIlizer/fdeep_model.json", true);


    String face_cascade_name = "C:/Users/Pinkie/source/repos/facAIlizer/haarcascade_frontalface_alt.xml";
    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };


    VideoCapture capture;
    //-- 2. Read the video stream
    capture.open(0);
    if (!capture.isOpened())
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }
    Mat frame;
    while (capture.read(frame))
    {
        if (frame.empty())
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay(frame);
        if (waitKey(10) == 27)
        {
            break; // escape
        }
    }
    return 0;
}
void detectAndDisplay(Mat frame)
{
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);

    // To declare finalOutputImg
    cv::Mat finalOutputImg;


    for (size_t i = 0; i < faces.size(); i++)
    {
        int x = faces[i].x;//Getting the initial row value of face rectangle's starting point//
        int y = faces[i].y;//Getting the initial column value of face rectangle's starting point//
        int h = y + faces[i].height;//Calculating the height of the rectangle//
        int w = x + faces[i].width;//Calculating the width of the rectangle//
        rectangle(frame, Point(x, y), Point(w, h), Scalar(255, 0, 255), 2, 8, 0);//Drawing a rectangle using around the faces//

        finalOutputImg = frame_gray(Rect(x, y, faces[i].x, faces[i].y));
        cv::resize(finalOutputImg, finalOutputImg, Size(48, 48));

        // To save image in root directory
        cv::imwrite("sampleImage.png", finalOutputImg);

        //not sure what this code does yet 
        Mat faceROI = frame_gray(faces[i]);
    }
    //-- Show what you got
    imshow("Capture - Face detection", frame);
}
