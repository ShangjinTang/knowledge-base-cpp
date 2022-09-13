# Preprocess

Preprocess commands start with "#", such as:

- #include
- #define
- #if
- #else
- ...

During the proprocess procedure, the original file is replaced to preprocessed `.ii` file.

All comments will be ignored in the preprocessed file.

## clang++

Generate the preprocessed file with 'clang++ -E' option:

```bash
clang++ --help | grep -e "^\s*-E"
  -E    Only run the preprocessor
```

```bash
clang++ -E hello_world.cpp > ./hello_world.ii
```

## g++

Generate the preprocessed file with 'g++ -E' option:

```bash
g++ -E hello_world.cpp > ./hello_world.ii
```
