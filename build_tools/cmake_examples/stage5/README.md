# Stage 5

This is similar to **Stage 4** but the files are slightly different.

Stage 4 directory structure:

- lib (.h & .cc under same directory)
- main (.h & .cc under same directory)

Stage 5 directory structure:

- lib (.h & .cc under seperate directories)
  - inc (.h file)
  - src (.cc file)
- main (.h & .cc under seperate directories)
  - inc (.h file)
  - src (.cc file)

To build this example, use

```bash
mkdir build
cd build
cmake ..
make
make run
```
