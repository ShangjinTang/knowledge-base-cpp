libhellogreet = library('hello-greet',
    ['hello-greet.cpp', 'hello-greet.h'],
)

helloworld = executable('hello-world',
    ['hello-world.cpp'],
    link_with: [libhellogreet],
)
