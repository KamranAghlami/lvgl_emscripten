#include "event/extensions.h"

#include <event/system.h>

typedef struct function_call_event_st
{
    event_system_async_function_t function;
    void *argument;
} function_call_event_t;

bool on_function_call_event(const function_call_event_t *e, void *user_data)
{
    e->function(e->argument);

    return true;
}

void event_system_extensions_enable(event_system_t *event_system)
{
    event_system_subscribe_to(event_system, function_call_event_t, on_function_call_event, NULL);
}

void event_system_extensions_disable(event_system_t *event_system)
{
    event_system_unsubscribe_from(event_system, function_call_event_t, on_function_call_event, NULL);
}

void _event_system_call_async(event_system_t *event_system, event_system_async_function_t function, void *argument)
{
    if (!function)
        return;

    const function_call_event_t e = {
        .function = function,
        .argument = argument,
    };

    event_system_dispatch_async(function_call_event_t, &e);
}
