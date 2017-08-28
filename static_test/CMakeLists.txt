cmake_minimum_required (VERSION 2.8)

project (StaticTest)

add_library(a
  a.cpp
  b.cpp)

add_executable(staticTest
  main.cpp
  )

target_link_libraries(staticTest
  a)
