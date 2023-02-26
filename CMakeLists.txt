# least version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5.0)

# project name
PROJECT(gemmkernel)

# link with pthread to set cpu affinity
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# set include path
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# file glob source files
FILE(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/*.S
)

# add executable latency_test
ADD_EXECUTABLE(latency_test latency.cpp ${SRC_FILES})
