cmake_minimum_required(VERSION 2.8.2)

SET(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_STRIP /usr/bin/arm-linux-gnueabihf-strip)
SET(CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(opencv_arm_test)

set(OpenCV_DIR "/home/pangbo/software/Opencv3.0_arm_v7/share/OpenCV")
find_package(OpenCV)

#set(dlib_DIR ../../Util/dlib_for_arm/dlib/install/lib/cmake/dlib)
#find_package(dlib)

include_directories(#${dlib_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS})

add_executable(opencv_arm_test main.cpp)

target_link_libraries(opencv_arm_test #${dlib_LIBRARIES}
    ${OpenCV_LIBRARIES})



