cmake_minimum_required(VERSION 3.15)
project(IoTRoutingSimulation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output binaries to /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(simulation ${SOURCES})

target_include_directories(simulation PRIVATE include)

# Enable warnings
if (MSVC)
    target_compile_options(simulation PRIVATE /W4)
else()
    target_compile_options(simulation PRIVATE -Wall -Wextra -Wpedantic)
endif()
