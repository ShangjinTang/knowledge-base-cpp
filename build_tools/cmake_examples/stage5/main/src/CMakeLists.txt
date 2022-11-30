file(GLOB main_src CONFIGURE_DEPENDS "*.cc")

add_executable(hello-world ${main_src})

target_link_libraries(hello-world libhellotime)

target_include_directories(hello-world PRIVATE ${LibIncDirectory})

add_custom_target(run
    COMMAND hello-world
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
