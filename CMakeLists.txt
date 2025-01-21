cmake_minimum_required(VERSION 3.10)

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_C_COMPILER "gcc" )

project(cLog)

# Add the cLog library
add_library(cLog STATIC src/cLog.c)

# Include directories for the library
target_include_directories(cLog PUBLIC inc)