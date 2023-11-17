# MIT License 
# Copyright (c) 2023 Shangjin Tang <shangjin.tang@gmail.com>
#
# Dependencies

# Required for Testing
if(BUILD_TESTING)
  find_package(doctest REQUIRED)
endif()

# Optional Dependency, doesn't trigger error if missing
find_package(OpenSSL)