# "cmake -DCMAKE_TOOLCHAIN_FILE=<conan_toochain.make>" requires cmake >= 3.15
# "cmake --preset conan-debug" requires cmake >= 3.23
cmake_minimum_required(VERSION 3.15)
project(tiny_regex_c_example C)

if(NOT TARGET tiny-regex-c)
  # Stand-alone build
  find_package(tiny-regex-c REQUIRED)
endif()

add_subdirectory(src)
