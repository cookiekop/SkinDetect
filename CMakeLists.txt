cmake_minimum_required(VERSION 3.9)
project(SkinDetector)

set(CMAKE_CXX_STANDARD 11)

add_executable(SkinDetector main.cpp)

find_package( OpenCV REQUIRED )

target_link_libraries(SkinDetector ${OpenCV_LIBS})