cmake_minimum_required(VERSION 3.3)
project(Sha2Proto)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SHA256.cpp SHA256.h SHA2_2.cpp SHA2_2.h)
add_executable(Sha2Proto ${SOURCE_FILES})