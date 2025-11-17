#ifndef EVENT_SYSTEM_EXTENSIONS_H
#define EVENT_SYSTEM_EXTENSIONS_H

#include <inttypes.h>

#define event_system_call_async_in(es, fn, arg) _event_system_call_async(es, (event_system_async_function_t)fn, arg)
#define event_system_call_async(fn, arg) event_system_call_async_in(event_system_global(), fn, arg)

typedef void (*event_system_async_function_t)(void *argument);
typedef struct event_system_st event_system_t;

void event_system_extensions_enable(event_system_t *event_system);
void event_system_extensions_disable(event_system_t *event_system);

void _event_system_call_async(event_system_t *event_system, event_system_async_function_t function, void *argument);

#endif
