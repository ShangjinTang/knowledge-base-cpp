# MIT License Copyright (c) 2023 Shangjin Tang <shangjin.tang@gmail.com>
#
# libdoctest target instructions

# ##############################################################################
# Define Target Information
# ##############################################################################
set(TARGET_NAME libdoctest)
set(TARGET_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# ##############################################################################
# Define Target according to options
# ##############################################################################
add_library(${TARGET_NAME} INTERFACE)

# ##############################################################################
# Define Target Properties
# ##############################################################################

# generate an export header to expose symbols when using the library
generate_export_header(${TARGET_NAME} EXPORT_FILE_NAME
                       ${CMAKE_BINARY_DIR}/exports/${TARGET_NAME}_export.h)

# add target properties such as debug postfix, MSVC Runtime and library version
set_target_properties(
  ${TARGET_NAME}
  PROPERTIES DEBUG_POSTFIX "-d"
             MSVC_RUNTIME_LIBRARY "${MSVC_RUNTIME_TYPE}"
             VERSION ${CMAKE_PROJECT_VERSION}
             SOVERSION ${CMAKE_PROJECT_VERSION})

# set target compile options as defined in the cmake/compiler_options.cmake
# Module
target_compile_options(${TARGET_NAME} INTERFACE ${compiler_options})

# add compiler definition
target_compile_definitions(${TARGET_NAME} INTERFACE ${compiler_definitions})

# set target link options as defined in the cmake/compiler_options.cmake Module
target_link_options(${TARGET_NAME} INTERFACE ${linker_flags})

# include all the necessary directories
target_include_directories(${TARGET_NAME} INTERFACE ${TARGET_INCLUDE_FOLDER})
