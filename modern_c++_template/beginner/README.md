# Conan 2.X with CMake

Install conan with python:

```python
python3 -m pip install conan
```

Go to [The Conan libraries and tools central repository](https://conan.io/center) and add to `conanfile.txt`

## Install Conan Pacakges

`.` indicates the `conanfile.txt` is at current directory.

### Debug

```bash
conan install . -s build_type=Debug --build=missing
```

### Release

```bash
conan install . -s build_type=Release --build=missing
```

## Build & Run (Command Line)

### Debug

```bash
cmake --preset conan-debug
cmake --build --preset conan-debug
./build/Debug/src/main
```

### Release

```bash
cmake --preset conan-release
cmake --build --preset conan-release
./build/Release/src/main
```

## Build & Run (CLion)

Install [Conan Plugin](https://plugins.jetbrains.com/plugin/11956-conan) in Settings - Plugins.
