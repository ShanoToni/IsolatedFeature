cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(IsolatedFeatureFinder)

#### Setup Directories ####
#Main output directory

SET (OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all the libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

### Solution ###
file(GLOB_RECURSE SOURCES *.cpp *.h)
add_executable(IsolatedFeatureFinder ${SOURCES})

