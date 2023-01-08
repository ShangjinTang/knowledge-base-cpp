file(GLOB lib_src CONFIGURE_DEPENDS "*.cpp")

add_library(libhellotime STATIC ${lib_src})

target_include_directories(libhellotime PRIVATE ${Main_SOURCE_DIR})
