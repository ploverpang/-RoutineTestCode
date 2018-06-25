cmake_minimum_required(VERSION 3.0.0)
project(ConstPtrTest VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -fPIC")

add_executable(ConstPtrTest const_ptr_test.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
