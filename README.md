# facAIlizer

This project was developed by Victor Ren, Scott Ho, Jessica Yang, Eric Wang and Chris Warcholyk.
The facAIlizer is designed to run on any windows, linux, or macOSx based machine.

# In order to develop the program, Microsoft Visual Studio Code was used as the IDE of choice.
Please ensure that your machine is paired with a functional UVC supported camera in order to avoid hardware related issues,
    as this program is functionally dependant on camera use.
Please ensure that all dependencies are previously installed, including frugally-deep as fdeep, Eigen3 as eigen, 
    FunctionalPlus as fplus, nlohmann_json as json, boost and opencv.
Trained fdeep.Models have already been included for use with the program.
    
# Upon all dependencies having been installed, please build the program with the following commands from ~/facAIlizer:

    #Build
    cd build && cmake ..
    make
    ./facAIlizer
    
# Upon running the program, a display window will open, and the camera will be taken as input and displayed within the window.
The facAIlizer program will detect and draw a rectangle around the faces of users present within the camera's vision,
    at which point it will begin determining the Gender and Emotion of each face detected in real time, displaying the info
    on the top of each rectangle --so that the relevant info is attatched to to the respective user-- and displaying the confidence
    levels as a bar graph for the first user.

# Reasons for dependency choices:
    fdeep:  for use with loading the models provided and the tensors.
    eigen:  for use with fdeep as a dependency.
    fplus:  for use with fdeep as a dependency
    json:   for use with fdeep and loading the models provided.   
    Boost:  for use with trimming tensor strings, and as an opencv dependency.
    Opencv: for use with working with the camera and display window.

# For help with dependencies:
    fdeep:  https://github.com/Dobiasd/frugally-deep/blob/master/INSTALL.md
    eigen:  https://gitlab.com/libeigen/eigen/-/blob/master/INSTALL
    fplus:  https://github.com/Dobiasd/FunctionalPlus/blob/master/INSTALL.md
    json:   https://github.com/nlohmann/json
    Boost:  https://github.com/boostorg/boost/blob/master/INSTALL
    Opencv: https://opencv.org/releases/    --Please ensure your release works with your machine.

#ENDofREADME
