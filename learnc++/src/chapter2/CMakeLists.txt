cmake_minimum_required (VERSION 3.5)

PROJECT(BuildAll) 
SET(SRC_LIST code2_1.cpp) 
#aux_source_directory(. DIR_SRCS)
SET(CMAKE_CXX_COMPILER "g++") 
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3") 
SET(CMAKE_BUILD_TYPE Debug) 
ADD_EXECUTABLE(program_name ${SRC_LIST})
INSTALL(PROGRAMS program_name DESTINATION /usr/bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./build/)
