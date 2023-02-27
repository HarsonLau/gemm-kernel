# least version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5.0)

# project name
PROJECT(gemmkernel)

# link with pthread to set cpu affinity
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# enbale assembly files
ENABLE_LANGUAGE( ASM)

# set include path
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# file glob source files
FILE(GLOB_RECURSE KERNEL_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/*.S
)

# file glob microbench src files
FILE(GLOB_RECURSE MICROBENCH_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microbench/*.S
    ${CMAKE_CURRENT_SOURCE_DIR}/src/microbench/*.cpp
)

# file glob common src files
FILE(GLOB_RECURSE COMMON_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp
)

# add executable latency_test
ADD_EXECUTABLE(latency_test latency.cpp ${COMMON_SRC_FILES} ${MICROBENCH_SRC_FILES})
ADD_EXECUTABLE(throughput_test throughput.cpp ${COMMON_SRC_FILES} ${MICROBENCH_SRC_FILES})
ADD_EXECUTABLE(main main.cpp ${COMMON_SRC_FILES} ${KERNEL_SRC_FILES} ${MICROBENCH_SRC_FILES})
