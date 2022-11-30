file(GLOB hello-world_src CONFIGURE_DEPENDS "*.h" "*.cc")

add_executable(hello-world ${hello-world_src})

target_link_libraries(hello-world PUBLIC libhellotime)

add_custom_target(run
    COMMAND hello-world
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
