cmake_minimum_required(VERSION 2.8.4)
project(infux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(SOURCE_FILES src/Infux.cpp src/Writer.cpp src/Reader.cpp src/Logos.cpp)
add_executable(infux ${SOURCE_FILES})
