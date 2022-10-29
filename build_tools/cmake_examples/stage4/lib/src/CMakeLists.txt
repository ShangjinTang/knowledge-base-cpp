include_directories(${Main_SOURCE_DIR}/lib/inc)

file(GLOB lib_src CONFIGURE_DEPENDS "*.cc")

add_library(lib ${lib_src})
