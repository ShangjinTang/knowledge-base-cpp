include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_library(loadable
  src/PluginManager.cpp
  src/linux.cpp
)

target_link_libraries(loadable ${CMAKE_DL_LIBS})

