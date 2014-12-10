cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project (piMotionDetector)
# The version number.
#set (Tutorial_VERSION_MAJOR 1)
#set (Tutorial_VERSION_MINOR 0)
 
# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
#  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
#  )

find_package( OpenCV REQUIRED )

#include_directories("${PROJECT_BINARY_DIR}")

set(RASPICAM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../robidouille/raspicam_cv)

include_directories(${RASPICAM_DIR})
link_directories(${RASPICAM_DIR})
 
# add the executable
add_executable(piMotionDetector PiMotionDetector/main.cpp)

target_link_libraries(piMotionDetector libraspicamcv.a)

#userland
target_link_libraries(piMotionDetector -L/home/pi/userland/build/lib mmal_core mmal mmal_util vcos bcm_host)

#open cv
target_link_libraries(piMotionDetector ${OpenCV_LIBS})

