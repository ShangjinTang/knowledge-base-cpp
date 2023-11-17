cmake_minimum_required(VERSION 3.12)
project(Main)

set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES
    ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

add_custom_target(
  run
  COMMENT "run prog"
  COMMAND prog
  DEPENDS prog
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_custom_target(
  gdb
  COMMENT "gdb prog"
  COMMAND gdb prog
  DEPENDS prog
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
