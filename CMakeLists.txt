cmake_minimum_required(VERSION 3.26)

project(hashiwokakero-qml)

# Testing
enable_testing()
find_package(GTest REQUIRED)

add_subdirectory(hashiwokakero-lib)
add_subdirectory(hashiwokakero)