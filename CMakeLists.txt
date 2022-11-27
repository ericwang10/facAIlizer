# CMakeList.txt : CMake project for facAIlizer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)

project ("facAIlizer")

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
find_package(frugally-deep CONFIG REQUIRED)
find_package (Eigen3 3.3 CONFIG REQUIRED)
find_package(FunctionalPlus CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (facAIlizer "facAIlizer.cpp" "facAIlizer.h")

# TODO: Add tests and install targets if needed.
target_link_libraries( facAIlizer ${OpenCV_LIBS} Eigen3::Eigen FunctionalPlus::fplus nlohmann_json frugally-deep::fdeep)
