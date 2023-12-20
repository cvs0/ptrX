# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(ptrX)

# Set C++ standard (adjust as needed)
set(CMAKE_CXX_STANDARD 11)

# Add your header files
file(GLOB_RECURSE HEADERS "include/*.h")

# Add the library target
add_library(ptrX INTERFACE)
target_sources(ptrX INTERFACE ${HEADERS})

# Set include directories
target_include_directories(ptrX INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
