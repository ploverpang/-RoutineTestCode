cmake_minimum_required(VERSION 3.0.0)
project(stl_algrithm_test VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_FLAGS "-std=c++0x")
add_executable(stl_algrithm_test stl_algrithm_test.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
