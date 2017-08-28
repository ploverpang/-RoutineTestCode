project(HelloWorld)

set(SRCList main.cpp)
add_executable(HelloWorld ${SRCList})
add_library(print HelloWorld.cpp)

target_link_libraries(HelloWorld print)
