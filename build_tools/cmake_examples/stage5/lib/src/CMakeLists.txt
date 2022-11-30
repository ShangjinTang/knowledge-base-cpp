file(GLOB lib_src CONFIGURE_DEPENDS "*.cc")

add_library(libhellotime ${lib_src})
