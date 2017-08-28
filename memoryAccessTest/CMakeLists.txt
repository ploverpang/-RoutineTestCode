PROJECT(MemoryAccessTest)

find_package(OpenCV REQUIRED)

add_executable(MemoryAccessTest ./memoryAccessTest.cpp)
target_link_libraries(MemoryAccessTest ${OpenCV_LIBS})


