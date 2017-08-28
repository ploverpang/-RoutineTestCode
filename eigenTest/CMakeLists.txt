cmake_minimum_required(VERSION 3.2)

project("eigen_test")

include_directories("/usr/include/eigen3")

set(SRC_LIST ${PROJECT_SOURCE_DIR}/eigenTest.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
