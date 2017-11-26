cmake_minimum_required(VERSION 2.6)
project(routinetest)

add_executable(routinetest A_impl.cpp A.cpp B.cpp B_impl.cpp main.cpp)

install(TARGETS routinetest RUNTIME DESTINATION bin)
