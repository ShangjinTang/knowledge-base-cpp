# Compile

Compilation step is take the input file `.ii` and generate the assembly code `.s`.

We'll generate `.s` from source file (not `.ii` file) as there is an `-S` option to run `preprocess` and `compile` steps at the same time..

## clang++

Generate the compiled file with 'clang++ -S' option:

```bash
clang++ --help | grep -e "^\s*-S"
  -S    Only run preprocess and compilation steps
```

```bash
clang++ -S hello_world.cpp
```

`hello_world.s` file will be generated.

Note:

- clang++ will have the step of generating `.bc` (bitcode) file between preprocessed file `.ii` and compiled file `.s`.
- We ignore this `.bc` bitcode generation part here as it's not a required step in g++.
- `.s` compiled file varies on different platforms (e.g. X86, X64, arm, ...).

## g++

Generate the preprocessed file with 'g++ -S' option:

```bash
g++ -S hello_world.cpp
```
