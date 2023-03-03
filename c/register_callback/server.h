#ifndef __SERVER_H__
#define __SERVER_H__

#define CALLBACK_MAX 10

typedef void (*callback_t)(void);

void register_callback(callback_t callback);
void run_callbacks(void);

#endif
