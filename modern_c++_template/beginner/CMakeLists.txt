# "cmake -DCMAKE_TOOLCHAIN_FILE=<conan_toochain.make>" requires cmake >= 3.15
# "cmake --preset conan-debug" requires cmake >= 3.23
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(conan_cmake_example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(lib)
add_subdirectory(main)

add_custom_target(
  run
  COMMENT "run main"
  COMMAND main
  DEPENDS main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(
  test_lib
  COMMENT "run test"
  COMMAND test_libmath
  DEPENDS test_libmath
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
