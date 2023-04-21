# Examples to build C++ code

This package will showcase how to build C++ code in stages.

### Stage 1
The first stage is really simple and shows you how to compile a binary with a single source file.

### Stage 2
The second stage will showcase how to build an application with multiple source and header files, separated in a library and a binary.

### Stage 3
The third stage showcases how to link multiple build directories by building multiple libraries in different packages and then connecting it up with the main application.

## Meson Domain Specific Language

### DO NOT USE HYPHEN('-') in TARGET

You cannot specify a target with hyphen('-'), for example:

1. In file `./main/meson.build`:

```meson
hello-world = executable('hello-world', 'hello-world.cpp')
```

Note: only assignment won't raise error.

2. In file `./meson.build`:

```meson
custom_target('main',
    command: [hello-world],
    output: 'main',
    build_by_default: true
)
```

Then compilation will raise error:

```
main/meson.build:1:0: ERROR: Assignment target must be an id.
hello-world = executable('hello-world', 'hello-world.cpp')
^
```
