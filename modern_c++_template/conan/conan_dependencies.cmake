# MIT License Copyright (c) 2023 Shangjin Tang <shangjin.tang@gmail.com>
#

# Required Dependencies
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)

# Required for Testing
if(BUILD_TESTING)
  find_package(doctest REQUIRED)
  find_package(GTest REQUIRED)
endif()

# Optional Dependencies, doesn't trigger error if missing
find_package(OpenSSL)
