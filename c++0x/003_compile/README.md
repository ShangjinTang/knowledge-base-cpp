# Compile

Compilation step is take the input file `.i` and generate the assembly code `.s`.

Since

## clang++

Check the compiled file with 'clang++ -S' option:

```bash
% clang++ --help | grep -e "^\s*-S"
  -S    Only run preprocess and compilation steps
```

```bash
clang++ -S hello_world.cpp
```

`hello_world.s` file will be generated.

Note: clang++ will have the step of generating `.bc` (bitcode) file between preprocessed file `.i` and compiled file `.s`.

We ignore this part here as it's not a required step in g++.

## g++

Check the preprocessed file with 'g++ -S' option:

```bash
g++ -S hello_world.cpp
```
