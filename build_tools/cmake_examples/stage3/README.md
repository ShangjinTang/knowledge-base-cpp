# Stage 3

To build this example, use

```bash
mkdir build
cd build
cmake ..
make
make run
```

## How to include header file 'directory/header.h'

Solution to include headers inside subdirectory with format `directory/header.h`, such as:

- `#include "lib/hello-time.h"`
- `#include "main/hello-greet.h"`

### Solution 1 (current solution)

Modify every CMakeLists.txt in subdirectories:

```cmake
target_include_directories(.. .. ${Main_SOURCE_DIR})
```

### Solution 2

Modify CMakeLists.txt in top directory:

```cmake
include_directories(".")
```

This will let any target include all directories from top directory.

In this case, this solution is easier, but still not recommended.
