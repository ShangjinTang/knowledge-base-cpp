# moderncpp-project-template

This repository aims to represent a template for Modern C++ projects, including static analysis checks, autoformatting, a BDD/TDD capable test-suite and packaging

## Requirements

- a modern C++17 compiler (`gcc-8`, `clang-6.0`, `MSVC 2017` or above)
- [`cmake`](https://cmake.org) 3.15+
- [`conan`](https://conan.io) 2.0+ (optional)
- `cppcheck` (optional)
- `clang-format` (optional)

## Features

- CMake-based project management, including dependencies
- Conan support for dependency management in CMake, completely optional
- Additional tools such as `clang-format` and `cppcheck`
- Support for shared/static libraries, including generation of export information
- Basic CPack configuration for redistributables

## Repository layout

The repository layout is pretty straightforward, including the CMake files to build the project, a `conanfile` where are declared examples of dependencies, a suppression list for cppcheck and the C++ source code:

```plain
-- conanfile.txt                - the main `conan` configuration file listing dependencies
-- cppcheck_suppressions.txt    - optional list of suppressions for cppcheck
-- CMakeLists.txt               - the main `CMake` Project configuration file
-- .dockerignore                - files to be excluded by Docker
-- .gitignore                   - files to be excluded by git
+- `cmake/`                     - CMake modules
  | -- clang-format.cmake       - CMake target definitions for clang-format
  | -- compiler-options.cmake   - Common compiler options for major platforms/compilers
  | -- cpack.cmake              - Packaging configuration with CPack
  | -- dependencies.cmake       - Project dependencies, CMake-Style
+- `project/`                   - the whole C++ project
  | -- .clang-format            - the formatter rules for the C++ project
  | -- CMakeLists.txt
  | +- `apphello/`              - your application files (including CMakeLists.txt, sources)
  | +- `libhello/`              - your library files (including CMakeLists.txt, sources
+- `build/`                     - working directory for the build
```

## Available CMake Options

- BUILD_TESTING - builds the tests (requires `doctest`)
- BUILD_SHARED_LIBS - enables or disables the generation of shared libraries
- BUILD_WITH_MT - valid only for MSVC, builds libraries as MultiThreaded DLL

If you activate the `BUILD_TESTING` flag, you need to perform in advance a `conan install` step, just to fetch the `doctest` dependency. Another dependency (OpenSSL) is used in this project as a demonstration of including a third-party library in the process, but it is totally optional and you can activate it only if you run conan in advance.

## How to build from command line

The project can be built using the following commands:

```bash
cd /path/to/this/project
conan install . --output-folder=. --build=missing
mkdir -p build       # md build (on Windows)
build_type="Release" # Debug / Release (Case Sensitive)
cmake -S . -B build/${build_type} -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DBUILD_TESTING=TRUE -DBUILD_SHARED_LIBS=TRUE -DCMAKE_BUILD_TYPE=${build_type} -DCMAKE_TOOLCHAIN_FILE=build/${build_type}/generators/conan_toolchain.cmake
cp build/${build_type}/compile_commands.json .
cmake --build build/${build_type}
cmake --build build/${build_type} --target format
cmake --build build/${build_type} --target package
```
