add_executable(hello-world hello-world.cc)

add_custom_target(
  run
  COMMAND hello-world
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
