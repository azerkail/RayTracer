# Specify the CMake minimum required version.
cmake_minimum_required(VERSION 3.28.1)

# Create a basic project named "RayTracer".
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
        Source/Files/FileHandler.cpp
        Source/Files/FileHandler.h
        Source/Logging/Log.cpp
        Source/Logging/Log.h
        Source/Maths/Vector3.cpp
        Source/Maths/Vector3.h
        Source/Renderers/FileRenderer.cpp
        Source/Renderers/FileRenderer.h
        Source/Engine.cpp
        Source/Engine.h
        Source/Renderers/IRenderer.h
        Source/Maths/Ray.cpp
        Source/Maths/Ray.h
        Source/Camera/Camera.cpp
        Source/Camera/Camera.h
        Source/Objects/Hittable.h
        Source/Objects/HitResult.h
        Source/Objects/HitResult.cpp
        Source/Objects/Sphere.cpp
        Source/Objects/Sphere.h
        Source/Collections/HittableVector.cpp
        Source/Collections/HittableVector.h
        Source/Constants.h
        Source/Utilities.h
        Source/RayTracerPCH.h
        Source/Maths/Interval.cpp
        Source/Maths/Interval.h
        Source/Materials/IMaterial.h
        Source/Materials/Lambertian.cpp
        Source/Materials/Lambertian.h
        Source/Materials/Metal.cpp
        Source/Materials/Metal.h
        Source/Materials/Dieletric.cpp
        Source/Materials/Dieletric.h
        Source/Maths/AABB.cpp
        Source/Maths/AABB.h
        Source/BVH/BVHNode.cpp
        Source/BVH/BVHNode.h)

# Set warning levels.
if(MSVC)
    target_compile_options(RayTracer PRIVATE /W4 /WX)
else()
    target_compile_options(RayTracer PRIVATE -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -Wno-unknown-pragmas)
endif()

# Precompiled headers.
target_precompile_headers(RayTracer PRIVATE Source/RayTracerPCH.h)

# spdlog
## Include spdlog header files.
target_include_directories(RayTracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Submodules/spdlog/include)
# End spdlog

# Include sub-directories to be able to include them directly.
target_include_directories(RayTracer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Source)
