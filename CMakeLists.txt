# CMake
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

# Project
project(Zmetek)
set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_MICRO 0)

# OGRE
find_package(OGRE 1.10 REQUIRED)
include_directories(${OGRE_INCLUDE_DIRS})
link_directories(${OGRE_LIBRARY_DIRS})

set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
set(DISTRIBUTION_DIR ${PROJECT_BINARY_DIR}/dist)

file(COPY ${RESOURCES_DIR}/plugins.cfg ${RESOURCES_DIR}/resources.cfg ${RESOURCES_DIR}/media DESTINATION ${DISTRIBUTION_DIR})

set(EXECUTABLE_OUTPUT_PATH ${DISTRIBUTION_DIR})

set(SOURCE_FILES src/main.cpp src/Zmetek.h src/Zmetek.cpp)
add_executable(zmetek ${SOURCE_FILES})
target_link_libraries(zmetek ${OGRE_LIBRARIES})