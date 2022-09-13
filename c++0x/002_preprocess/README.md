# Preprocess

Preprocess commands start with "#", such as:

- #include
- #define
- #if
- #else
- ...

During the proprocess procedure, the original file is replaced to preprocessed (.i) file.

All comments will be ignored in the preprocessed file.

## g++

Check the preprocessed file with 'g++ -E' option:

```bash
g++ -E hello_world.cpp > ./hello_world.i
```

## clang++

Check the preprocessed file with 'clang++ -E' option:

```bash
clang++ -E hello_world.cpp > ./hello_world.i
```
