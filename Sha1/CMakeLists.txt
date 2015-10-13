cmake_minimum_required(VERSION 3.3)
project(Sha1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp sha2.cpp sha2.h)
add_executable(Sha1 ${SOURCE_FILES})