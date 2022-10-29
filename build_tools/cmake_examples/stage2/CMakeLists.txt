cmake_minimum_required(VERSION 3.12)
project(Main)

set(CMAKE_CXX_STANDARD 20)

file(GLOB hello-world_src CONFIGURE_DEPENDS "main/*.h" "main/*.cc")

add_executable(hello-world ${hello-world_src})
