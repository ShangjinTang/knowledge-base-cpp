#!/usr/bin/env bash

clean() {
    rm -rf ./build &> /dev/null
}

conan_install() {
    conan install . -s build_type=Debug --build=missing
}

cmake_compile() {
    cmake -S . -B build/Debug -DCMAKE_TOOLCHAIN_FILE=build/Debug/generators/conan_toolchain.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug
    cp build/Debug/compile_commands.json .
    # cmake --build build/Debug --config Debug
}

cmake_run() {
    cmake --build build/Debug --config Debug --target run
}

clean
conan_install
cmake_compile
cmake_run
