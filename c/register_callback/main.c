#include <stdio.h>

#include "server.h"

void foo(void) {
    puts("foo!");
}

void bar(void) {
    puts("bar!");
}

int main(void) {
    register_callback(&foo);
    register_callback(&bar);

    run_callbacks();

    return 0;
}
