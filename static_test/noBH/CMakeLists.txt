cmake_minimum_required (VERSION 2.8)

project (StaticTest)

add_executable(staticTest
  main.cpp
  )

target_link_libraries(staticTest
  abc)
