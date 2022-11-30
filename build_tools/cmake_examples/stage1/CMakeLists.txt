cmake_minimum_required(VERSION 3.12)
project(Main)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(hello-world main/hello-world.cc)

add_custom_target(run
    COMMAND hello-world
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
