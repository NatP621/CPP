# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TreeDrawing VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable compile warnings for all files
set(COMMON_COMPILE_OPTIONS "-Wall" "-Wextra" "-Wpedantic")

# Define the source files
set(SOURCES
        Test.cpp
        tree.hpp
        tree.tpp
)

# Create the executable target
add_executable(test_tree ${SOURCES})

# Link SFML libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(test_tree PRIVATE sfml-graphics sfml-window sfml-system)

# Set include directories
target_include_directories(test_tree PRIVATE ${CMAKE_SOURCE_DIR})

# Apply common compile options for better code safety
target_compile_options(test_tree PRIVATE ${COMMON_COMPILE_OPTIONS})

# Print project info after build configuration
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")