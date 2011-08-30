#dane dla calego projektu ogolnie
#dolaczenie odpowiednich katalogow
cmake_minimum_required(VERSION 2.6)
project(safarix)
set(CMAKE_BUILD_TYPE "Debug")
add_subdirectory(src)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
