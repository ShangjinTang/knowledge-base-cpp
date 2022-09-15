include_directories(${Main_SOURCE_DIR}/main/inc)
include_directories(${Main_SOURCE_DIR}/lib/inc)

link_directories(${Main_SOURCE_DIR}/lib/src)

file(GLOB main_src CONFIGURE_DEPENDS "*.cc")

add_executable(hello-world ${main_src})

target_link_libraries(hello-world lib)
