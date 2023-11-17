add_executable(main main.c)
target_link_libraries(main PRIVATE tiny-regex-c::tiny-regex-c)

add_custom_target(
  run
  COMMENT "run main"
  COMMAND main
  DEPENDS main
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
