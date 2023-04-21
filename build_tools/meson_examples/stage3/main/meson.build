libhellogreet = library('hello-greet',
    ['hello-greet.cpp', 'hello-greet.h'],
    include_directories: [mainincdir],
)

helloworld = executable('hello-world',
    ['hello-world.cpp'],
    include_directories: [mainincdir],
    link_with: [libhellogreet, libhellotime],
)
