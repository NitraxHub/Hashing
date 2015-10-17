cmake_minimum_required(VERSION 3.3)
project(Sha1Proto)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Sha1.cpp Sha1.h)
add_executable(Sha1Proto ${SOURCE_FILES})