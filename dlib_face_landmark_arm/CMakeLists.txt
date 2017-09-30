cmake_minimum_required(VERSION 2.8.2)
project(face_landmark)

set(OpenCV_DIR "/home/pangbo/software/Opencv3.0_arm_v7/share/OpenCV")
find_package(OpenCV)

#set(dlib_DIR "/home/pangbo/software/dlib_arm_v7/lib/cmake/dlib")
set(dlib_DIR "/home/pangbo/software/dlib_arm_v7_neon/lib/cmake/dlib")
find_package(dlib)

set(CMAKE_BUILD_TYPE RELEASE)

include_directories(${dlib_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -march=armv7 -mfpu=neon -std=c++0x" )

add_executable(face_landmark main.cpp)

target_link_libraries(face_landmark ${dlib_LIBRARIES}
    ${OpenCV_LIBRARIES})



