cmake_minimum_required(VERSION 3.12)
project(Main)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

add_custom_target(run
    COMMAND src/prog
    DEPENDS src/prog
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(lldb
    COMMAND lldb src/prog
    DEPENDS src/prog
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
