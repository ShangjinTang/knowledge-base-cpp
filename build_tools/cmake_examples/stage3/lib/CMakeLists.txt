file(GLOB lib_src CONFIGURE_DEPENDS "*.cc")

add_library(libhellotime STATIC ${lib_src})

target_include_directories(libhellotime PRIVATE ${Main_SOURCE_DIR})
