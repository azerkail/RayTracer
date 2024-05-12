# Specify the CMake minimum required version.
cmake_minimum_required(VERSION 3.29)

# Create a basic project named "Avernus".
project(RayTracer VERSION 0.1.0 LANGUAGES CXX)

# Stop CMake from prefixing "lib" to output file.
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Set the C++ version.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Warnings as errors.
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Set compiler flags per system.
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# Create an executable to run the sandbox with.
add_executable(RayTracer main.cpp
        Source/FileHandler.cpp
        Source/FileHandler.h)

# Include sub-directories to be able to include them directly.
target_include_directories(RayTracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Source)
