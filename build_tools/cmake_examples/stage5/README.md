# Stage 5

This is similar to **Stage 4** but the files are slightly different.

Stage 4 directory structure:

- lib (.h & .cpp under same directory)
- main (.h & .cpp under same directory)

Stage 5 directory structure:

- lib (.h & .cpp under seperate directories)
  - inc (.h file)
  - src (.cpp file)
- main (.h & .cpp under seperate directories)
  - inc (.h file)
  - src (.cpp file)

To build this example, use

```bash
mkdir build
cd build
cmake ..
make
make run
```
