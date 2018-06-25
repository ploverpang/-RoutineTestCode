cmake_minimum_required(VERSION 3.0.0)
project(DereveClassCastTest VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(DereveClassCastTest derive_class_cast.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -fPIC")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
