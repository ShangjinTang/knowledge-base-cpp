file(GLOB hello-world_src CONFIGURE_DEPENDS "*.h" "*.cpp")

add_executable(hello-world ${hello-world_src})

target_include_directories(hello-world PRIVATE ${Main_SOURCE_DIR}/lib)

target_link_libraries(hello-world PRIVATE libhellotime)

add_custom_target(
  run
  COMMAND hello-world
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
