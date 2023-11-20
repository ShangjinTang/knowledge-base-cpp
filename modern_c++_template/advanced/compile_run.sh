#!/usr/bin/env bash

# pip3 install conan
# conan profile detect --force

rm -rf build &> /dev/null

conan install . -s build_type=Debug --build=missing
# cmake -S . -B build/Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=TRUE -DCMAKE_TOOLCHAIN_FILE=build/Debug/generators/conan_toolchain.cmake
cmake -S . -B build/Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=TRUE -DCMAKE_TOOLCHAIN_FILE=build/Debug/generators/conan_toolchain.cmake
cp build/Debug/compile_commands.json .
cmake --build build/Debug --config Debug
ctest --test-dir build/Debug --output-on-failure
