// facAIlizer.cpp : Defines the entry point for the application.
//

#include "facAIlizer.h"




using namespace std;
using namespace cv;
void detectAndDisplay(Mat frame);
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

//load model 
const auto model = fdeep::load_model("./fdeep_model5.json", true);
const auto model_mask = fdeep::load_model("./fdeep_model_mask.json", true);

int main(int argc, const char** argv)
{

    String face_cascade_name = "./haarcascade_frontalface_alt.xml";
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
            //break;
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
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    cvtColor(frame, frame_gray, COLOR_RGB2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);

    // To declare finalOutputImg, i think don't put it as const since it will continuously change 
    cv::Mat finalOutputImg;

    if (faces.size() == 0) {
        return;
    }

    for (size_t i = 0; i < faces.size(); i++)
    {
        int x = faces[i].x;//Getting the initial row value of face rectangle's starting point//
        int y = faces[i].y;//Getting the initial column value of face rectangle's starting point//
        int h = y + faces[i].height;//Calculating the height of the rectangle//
        int w = x + faces[i].width;//Calculating the width of the rectangle//
        rectangle(frame, Point(x, y), Point(w, h), Scalar(255, 0, 255), 2, 8, 0);//Drawing a rectangle using around the faces//

        finalOutputImg = frame_gray(Rect(x, y, faces[i].height, faces[i].width));
        cv::resize(finalOutputImg, finalOutputImg, Size(48, 48));
        finalOutputImg.convertTo(finalOutputImg, -1, 1, 50);

        // To save image in root directory
        cv::imwrite("sampleImage.png", finalOutputImg);

        //LOAD INTO MODEL
        assert(finalOutputImg.isContinuous());
        const auto input = fdeep::tensor_from_bytes(finalOutputImg.ptr(),
            static_cast<std::size_t>(finalOutputImg.rows),
            static_cast<std::size_t>(finalOutputImg.cols),
            static_cast<std::size_t>(finalOutputImg.channels()),
            0.0f, 255.0f);

        //MASK DETECTOR
        const auto result_mask = model_mask.predict_class({ input });
        std::cout << "Mask is: " << result_mask << endl;
        if (result_mask == 2) {
            std::cout << "masked" << endl;
        }

        //EMOTION DETECTOR
        const auto result = model.predict({ input });
        std::cout << fdeep::show_tensors(result) << std::endl;
        //std::cout << "fdeep input is: " << fdeep::show_tensor(input) << std::endl;
        std::cout << "fdeep input.shape() is: " << fdeep::show_tensor_shape(input.shape()) << std::endl;
        std::cout << "fdeep result.front().shape() is: " << fdeep::show_tensor_shape(result.front().shape()) << std::endl;


        //not sure what this code does yet 
        Mat faceROI = frame_gray(faces[i]);
    }
    //-- Show what you got
    imshow("Capture - Face detection", frame);
}
