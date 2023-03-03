#include "server.h"

#include <stdio.h>

static callback_t callbacks[CALLBACK_MAX];
static unsigned int n = 0;

void register_callback(callback_t callback) {
    if (n == CALLBACK_MAX)
        return;

    callbacks[n++] = callback;
}

void run_callbacks(void) {
    for (unsigned int i = 0; i < n; i++) {
        callbacks[i]();
    }
}
