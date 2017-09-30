cmake_minimum_required(VERSION 2.8.2)
project(face_landmark)

set(OpenCV_DIR "/usr/local/share/OpenCV")
find_package(OpenCV)

set(dlib_DIR ../../Util/dlib/install/lib/cmake/dlib)
find_package(dlib)

include_directories(${dlib_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS})

add_executable(face_landmark main.cpp)

target_link_libraries(face_landmark ${dlib_LIBRARIES}
    ${OpenCV_LIBRARIES})



