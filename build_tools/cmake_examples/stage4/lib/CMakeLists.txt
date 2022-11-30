file(GLOB lib_src CONFIGURE_DEPENDS "*.cc")

add_library(libhellotime STATIC ${lib_src})
