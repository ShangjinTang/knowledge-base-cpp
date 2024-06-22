# MIT License Copyright (c) 2023-2024 Shangjin Tang <shangjin.tang@gmail.com>
#
# External Dependencies

find_package(cppzmq QUIET REQUIRED)
find_package(protobuf QUIET REQUIRED)
if(BUILD_TESTING)
  find_package(GTest QUIET REQUIRED)
endif()

# ##############################################################################

# common libraries
list(APPEND COMMON_LINKED_LIBRARIES cppzmq)
list(APPEND COMMON_LINKED_LIBRARIES protobuf::protobuf)

# test libraries
list(APPEND COMMON_LINKED_TEST_LIBRARIES gtest gtest_main)

# ##############################################################################
