file(GLOB lib_src CONFIGURE_DEPENDS "src/*.cpp")

add_library(libhellotime STATIC ${lib_src})

target_include_directories(libhellotime PRIVATE inc)
