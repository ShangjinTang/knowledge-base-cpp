# Stage 3

Note: the `include_directories(".")` in top `CMakeLists.txt` is very important.
Without this, we cannot include sources with subdirectory such as `#include "lib/hello-time.h"` or `#include "main/hello-greet.h"`.

To build this example, use

```bash
mkdir build
cd build
cmake ..
make
make run
```
