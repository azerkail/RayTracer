# Ray Tracer

Study and implementation of a simple ray tracer using the [Ray Tracing In One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) book.

All of the mathematical formulas were taken from the book, however, coding structure, style, naming conventions and most design
decisions were altered to fit what I believe is the best C++ I can write.

Current final render:

![Final Render](https://github.com/azerkail/RayTracer/blob/main/Renders/2024-05-20.png)

# Roadmap

The following roadmap details the direction with which I'm planning to take this project:
1. ✅ Follow `Ray Tracing In One Weekend`
2. ✅ Follow `Ray Tracing The Next Week`

# Building & Running

The project is built to run with CMake, I have configured the project using CLion which will provide some configuration
files for you automatically through the .idea folder.

If using CLion:
1. Make sure your build settings are set to either Debug/Release
2. Build/run the `RayTracer` build configuration 
3. The executable is placed under `./bin/Debug` for debug builds and `./bin/Release`
for release builds which will allow you to debug and run respectively

If you want to use the command line, then:
1. My recommendation is to make sure you have CMake and Ninja installed and available in the command line in your system
2. This command both builds the makefile with CMake and the executable with Ninja: `cmake -DCMAKE_BUILD_TYPE=Release -G Ninja -S ./RayTracer -B ./.bin/Release`
   1. If you need to debug the project, swap from Release to Debug 
3. This should produce a `RayTracer` executable file for you, under `.bin/Release` which you can execute from the command line.
