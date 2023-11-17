include_directories(${PROJECT_SOURCE_DIR}/lib/inc)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE fmt::fmt spdlog::spdlog gtest gtest_main)
target_link_libraries(main PRIVATE libmath)
