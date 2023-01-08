file(GLOB lib_src CONFIGURE_DEPENDS "*.cpp")

add_library(libhellotime STATIC ${lib_src})
