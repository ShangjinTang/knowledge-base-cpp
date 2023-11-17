# "cmake -DCMAKE_TOOLCHAIN_FILE=<conan_toochain.make>" requires cmake >= 3.15
# "cmake --preset conan-debug" requires cmake >= 3.23
cmake_minimum_required(VERSION 3.15)
project(conan_cmake_example CXX)

if(NOT TARGET spdlog)
  # Stand-alone build
  find_package(spdlog REQUIRED)
endif()

if(NOT TARGET fmt)
  # Stand-alone build
  find_package(fmt REQUIRED)
endif()

add_subdirectory(src)

add_custom_target(
  run
  COMMENT "run main"
  COMMAND main
  DEPENDS main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
