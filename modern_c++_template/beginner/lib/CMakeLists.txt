set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB lib_src CONFIGURE_DEPENDS "src/*.cpp")

add_library(libmath STATIC ${lib_src})

target_include_directories(libmath PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(test_libmath "test/test_math.cpp")
target_include_directories(test_libmath PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(test_libmath PRIVATE libmath gtest gtest_main)
