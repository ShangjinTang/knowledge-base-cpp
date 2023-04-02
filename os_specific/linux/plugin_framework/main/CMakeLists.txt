include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../loadable/inc)

# if there is libhello.so file, use the copy command to target folder
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib/libhello.so DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# if there is no libhello.so file, compile it from source and specify target folder
add_library(hello
  SHARED
  lib/hello_module.cpp
)
set_target_properties(hello
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
) 

add_executable(main
  src/main.cpp
)

target_link_libraries(main loadable)

