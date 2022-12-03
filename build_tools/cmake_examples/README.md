# CMake examples to build C++ code

This package will showcase how to build C++ code in stages.

### Stage 1
The first stage is really simple and shows you how to compile a binary with a single source file.

### Stage 2
The second stage will showcase how to build an application with multiple source and header files, separated in a library and a binary.

### Stage 3
The third stage showcases how to link multiple build directories by building multiple libraries in different packages and then connecting it up with the main application.

## How to format cmake file

Reference: [cmake_format](https://github.com/cheshirekow/cmake_format)

```python
pip3 install cmakelang
```

Without sudo, `cmake-format` is default installed to `~/.local/bin`.

```python
~/.local/bin/cmake-format -i CMakeLists.txt
```

`-i` means `--in-place` to replace original CMakeLists.txt
