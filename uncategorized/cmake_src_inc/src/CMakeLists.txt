include_directories(${Main_SOURCE_DIR}/inc)

link_directories(${Main_SOURCE_DIR}/src)

file(GLOB main_src CONFIGURE_DEPENDS "*.cc" "*.cpp")

add_executable(prog ${main_src})
