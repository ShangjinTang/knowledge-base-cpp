cmake_minimum_required(VERSION 3.12)
project(Main)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB hello-world_src CONFIGURE_DEPENDS "main/*.h" "main/*.cc")

add_executable(hello-world ${hello-world_src})

add_custom_target(run
    COMMAND hello-world
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
