# Assemble

Compilation step is take the input file `.s` and generate the assembly code `.o`.

We'll generate `.o` from source file (not `.o` file) as there is an `-c` option to run `preprocess`, `compile` and `assemble` steps at the same time..

## clang++

Check the compiled file with 'clang++ -c' option:

```bash
clang++ --help | grep -e "^\s*-c\s\+"
  -c    Only run preprocess, compile, and assemble steps
```

```bash
clang++ -c hello_world.cpp
```

`hello_world.o` file will be generated.

## g++

Check the preprocessed file with 'g++ -c' option:

```bash
g++ -c hello_world.cpp
```
