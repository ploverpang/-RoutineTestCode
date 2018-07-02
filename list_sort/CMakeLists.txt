cmake_minimum_required(VERSION 3.0.0)
project(list_sort VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(list_sort main.cpp)

set(CMAKE_CXX_FLAGS "-std=c++0x")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
