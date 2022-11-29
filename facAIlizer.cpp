/*! @brief main facAIlizer class to use models 
 * Detailed description follows here.
 * @author Team 19
 * @date 2022-11-28
*/


#include "facAIlizer.h"
#include <boost/algorithm/string.hpp>


using namespace std;
using namespace cv;
void detectAndDisplay(cv::Mat frame);
CascadeClassifier face_cascade; /**< supports face cascade*/
CascadeClassifier eyes_cascade; /**< supports eye cascade*/

const auto model = fdeep::load_model("./fdeep_model3.json", true); /**< loads fdeep model for facial expressions*/
const auto model_gender = fdeep::load_model("./fdeep_model_gender.json", true); /**< loads fdeep model for gender*/

string emoteList[6] = {"Angry", "Fearful", "Happy", "Neutral", "Sad", "Surprised"};

/*!
   main method initializes xml and video capture, connects rest of code to detect facial expressions
*/
int main(int argc, const char** argv)
{

    String face_cascade_name = "./haarcascade_frontalface_alt.xml"; /**< path to face cascade*/
    
    //! 1. load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };


    VideoCapture capture;
    //! 2. Read the video stream
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
        //! 3. Apply the classifier to the frame
        detectAndDisplay(frame);
        if (waitKey(10) == 27)
        {
            break; // escape
        }
    }
    return 0;
}

/*! detectAndDisplay detects users face and displays the camera capture
    \param frame gives the frame size
*/
void detectAndDisplay(Mat frame)
{
    //! sets up the display frame color and size
    Mat frame_gray;
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    cvtColor(frame, frame_gray, COLOR_RGB2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //! Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);

    
    cv::Mat finalOutputImg; /**< loads final image*/
    if (faces.size() == 0) {
        return;
    }


    for (size_t i = 0; i < faces.size(); i++)
    {
        string decision = ""; 
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



        //Gender Identifier
        const auto result_gender = model_gender.predict({ input });
        //std::cout << "Gender var is: " << result_gender << endl;
        std::cout << "Gender tensors " << fdeep::show_tensors(result_gender) << std::endl;
        std::string gender_stat = fdeep::show_tensors(result_gender);

        boost::trim_left_if(gender_stat, boost::is_any_of("[")); 
        boost::trim_right_if(gender_stat, boost::is_any_of("]"));
        std::string delimiter = ", ";

        size_t pos = 0;
        int count = 0;
        std::string token1;
        double genderArray[2];

        while ((pos = gender_stat.find(delimiter)) != std::string::npos) {
            token1 = gender_stat.substr(0, pos);
            //std::cout << std::stod(token) << endl;
            genderArray[count] = std::stod(token1);
            //std::cout << token << std::endl;
            gender_stat.erase(0, pos + delimiter.length());
            count++;
        }
        token1 = gender_stat.substr(0, pos);
        genderArray[count] = std::stod(token1);


        if (genderArray[1] > 0.5) {
            decision = "Male: ";
            //std::cout << "Male" << endl;
        }
        else {
            decision = "Female: ";
            //std::cout << "Female" << endl;
        }


        //EMOTION DETECTOR
        const auto result = model.predict({ input });
        std::cout << fdeep::show_tensors(result) << std::endl;
        std::string emotions_stats = fdeep::show_tensors(result);
        boost::trim_left_if(emotions_stats, boost::is_any_of("[")); 
        boost::trim_right_if(emotions_stats, boost::is_any_of("]")); 


        pos = 0;
        count = 0;
        std::string token2;
        double emotionsArray[6];

        while ((pos = emotions_stats.find(delimiter)) != std::string::npos) {
            token2 = emotions_stats.substr(0, pos);
            emotionsArray[count] = std::stod(token2);
            emotions_stats.erase(0, pos + delimiter.length());
            count++;
        }
        token2 = emotions_stats.substr(0, pos);
        emotionsArray[count] = std::stod(token2);

        printf("\n");
        for (int i=0; i<6; i++){
            std::cout << emotionsArray[i] << std::endl;
        }
        printf("\n");

        double highestEmotion = 0;
        int highestIndex = 0;
        for (int i=0; i<6; i++) {
            if (emotionsArray[i] > highestEmotion) {
                highestEmotion = emotionsArray[i];
                highestIndex = i;
            }
        }

        decision += emoteList[highestIndex];
        cout << highestIndex << endl;
        //cout << << endl;
        cv::putText(frame, decision, Point(x, y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.9, CV_RGB(0,255,0), 2); //COLOR IS SCALAR


        //create graphs
        int sep = 50;
        int probability = 50;
        for (int i = 0; i < 6; i++) {
            Scalar color(0, 0, 255);

            if (i == highestIndex) {
                color = Scalar(0, 255, 0);
            }
            rectangle(frame, Point(30 + i * sep, 400), Point(30 + i * sep + 20 , 400 - emotionsArray[i] * (frame.size().height/3)), color, FILLED, 8, 0);//Drawing a rectangle using around the faces//
            cv::putText(frame, emoteList[i], Point(30 + i * sep - 25, 430), cv::FONT_HERSHEY_SIMPLEX, 0.5, color, 2); //COLOR IS SCALAR
        }


        std::cout << std::endl;

        //not sure what this code does yet 
        Mat faceROI = frame_gray(faces[i]);
    }
    //-- Show what you got
    imshow("Capture - Face detection", frame);
}
