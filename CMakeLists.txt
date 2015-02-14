cmake_minimum_required(VERSION 2.8.4)
project(infux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES infux.cpp)
add_executable(infux ${SOURCE_FILES})
