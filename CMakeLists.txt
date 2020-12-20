cmake_minimum_required(VERSION 3.5)

project(test_task CXX ${PROJECT_NAME})


set(CMAKE_CXX_COMPILER "/usr/lib64/openmpi/bin/mpicxx")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

find_path (MPI_INCLUDES_CXX mpicxx HINTS MPI_DIR MPI_DIR)
message(" inc =  ${MPI_INCLUDES_CXX}  ")
find_library (MPI_LIBRARIES_CXX  NAMES mpicxx)
message(" lib =  ${MPI_LIBRARIES_CXX}  ")

include_directories(SYSTEM ${MPI_INCLUDE_PATH} PRIVATE ${MPI_CXX_INCLUDE_PATH})

file(GLOB SOURCES
    *.cpp)



add_executable(${PROJECT_NAME} ${SOURCES} )

target_link_libraries (${PROJECT_NAME} ${MPI_CXX_LIBRARIES})
