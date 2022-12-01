file(GLOB main_src CONFIGURE_DEPENDS "src/*.cc")

add_executable(hello-world ${main_src})

target_link_libraries(hello-world PRIVATE libhellotime)

target_include_directories(hello-world PRIVATE inc ${Main_SOURCE_DIR}/lib/inc)

add_custom_target(
  run
  COMMAND hello-world
  WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
