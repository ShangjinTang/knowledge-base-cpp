cmake_minimum_required(VERSION 3.12)
project(Main)

set(CMAKE_CXX_STANDARD 20)

file(GLOB hello-world_src CONFIGURE_DEPENDS "main/*.h" "main/*.cc")

add_subdirectory(lib)

add_executable(hello-world ${hello-world_src})

target_link_libraries(hello-world PUBLIC lib)

target_include_directories(hello-world PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib"
                          )
