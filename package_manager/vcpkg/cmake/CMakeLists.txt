# "cmake -DCMAKE_TOOLCHAIN_FILE=<conan_toochain.make>" requires cmake >= 3.15
# "cmake --preset conan-debug" requires cmake >= 3.23
cmake_minimum_required(VERSION 3.15)
project(conan_cmake_example CXX)

find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

add_subdirectory(src)

add_custom_target(
  run
  COMMENT "run main"
  COMMAND main
  DEPENDS main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
