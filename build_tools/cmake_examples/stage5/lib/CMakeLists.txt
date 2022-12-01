file(GLOB lib_src CONFIGURE_DEPENDS "src/*.cc")

add_library(libhellotime STATIC ${lib_src})

target_include_directories(libhellotime PRIVATE inc)
