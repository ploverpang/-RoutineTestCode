cmake_minimum_required(VERSION 2.8.2)

project(BoostProgramOptionsTest)

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED COMPONENTS
    program_options)

if(NOT Boost_FOUND)
    message("Not found Boost")
endif()

include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)

link_directories(${Boost_LIBRARY_DIR})

message("Boost_LIBRARY_DIR is ${Boost_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})



