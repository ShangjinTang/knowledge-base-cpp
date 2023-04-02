cmake_minimum_required(VERSION 3.12)
project(Main)

set(CMAKE_CXX_STANDARD 20)

# add line below to avoid error when using clang-uml
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

# set(CMAKE_STATIC_LIBRARY_PREFIX "")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-W -Wall -Werror)
endif()

add_subdirectory(loadable)
add_subdirectory(main)

add_custom_target(run
    COMMAND $<TARGET_FILE:main>
    DEPENDS main hello
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

