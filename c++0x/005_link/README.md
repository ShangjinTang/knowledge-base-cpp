# Link

Generate the executable file `a.out` by the linker.

## clang++

```bash
clang++ hello_world.o
```

`a.out` file will be generated.

Alternatively, we can use `-o` option to specify the output file name.

```bash
clang++ hello_world.o -o hello_world
```

This is actually by the linker.

For example, `std::cout` is defined and implemented in standard library, so the linker will find it (actually here is is `libstdc++.so` ) and link to `hello_world.o` file.

Note:

- We can also use the original source code file to generate executable file (instead of `.o` file).

### ldd

We can use `ldd` to check which libraries are linked for the executable file.

```bash
ldd a.out 
    linux-vdso.so.1 (0x00007fffdc1fb000)
    libstdc++.so.6 => /lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f4000757000)
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f4000608000)
    libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f40005ed000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f40003fb000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f4000950000)
```

## g++

```bash
g++ hello_world.o
```

`a.out` file will be generated.

Alternatively, we can use `-o` option to specify the output file name.

```bash
g++ hello_world.o -o hello_world
```
