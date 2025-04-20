#include "event/system.h"

#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <lvgl.h>

#define _max(x, y) (((x) > (y)) ? (x) : (y))

#define DEFAULT_ENTRY_CAPACITY 8
#define DEFAULT_ASYNC_CAPACITY 256

typedef struct event_system_entry_st
{
    const char *type;
    event_system_handler_t handler;
    void *user_data;
} event_system_entry_t;

struct event_system_st
{
    size_t capacity;
    size_t count;
    event_system_entry_t *entries;

    struct
    {
        size_t capacity;
        size_t size;
        uint8_t *events;
    } async;

    bool is_locked;
};

typedef struct event_system_async_event_st
{
    const char *type;
    size_t stride;
    uint8_t data[1];
} event_system_async_event_t;

typedef struct subscribe_event_st
{
    event_system_t *event_system;
    const char *type;
    event_system_handler_t handler;
    void *user_data;
} ___subscribe_event_t;

typedef struct unsubscribe_event_st
{
    event_system_t *event_system;
    const char *type;
    event_system_handler_t handler;
    void *user_data;
} ___unsubscribe_event_t;

static event_system_t *g_event_system = NULL;

static size_t first_index_after(const event_system_t *event_system, const char *type)
{
    const event_system_entry_t *entries = event_system->entries;
    const size_t count = event_system->count;

    size_t left = 0, right = count;

    while (left < right)
    {
        const size_t mid = left + (right - left) / 2;

        if (strcmp(type, entries[mid].type) >= 0)
            left = mid + 1;
        else
            right = mid;
    }

    return left;
}

static size_t first_index_of(const event_system_t *event_system, const char *type)
{
    const event_system_entry_t *entries = event_system->entries;
    const size_t count = event_system->count;

    size_t index = count;
    size_t left = 0, right = count;

    while (left < right)
    {
        const size_t mid = left + (right - left) / 2;

        if (strcmp(type, entries[mid].type) <= 0)
        {
            if (strcmp(type, entries[mid].type) == 0)
                index = mid;

            right = mid;
        }
        else
            left = mid + 1;
    }

    return index;
}

static bool on_subscribe_event(const ___subscribe_event_t *e, void *user_data)
{
    const size_t capacity = e->event_system->capacity;
    const size_t count = e->event_system->count;

    if (count == capacity)
    {
        const size_t new_capacity = capacity + capacity / 2;

        e->event_system->entries = lv_realloc(e->event_system->entries, new_capacity * sizeof(event_system_entry_t));
        e->event_system->capacity = new_capacity;
    }

    const size_t index = first_index_after(e->event_system, e->type);

    event_system_entry_t *entries = e->event_system->entries;

    if (index < count)
        memmove(&entries[index + 1], &entries[index], (count - index) * sizeof(event_system_entry_t));

    e->event_system->entries[index] = (event_system_entry_t){
        .type = e->type,
        .handler = e->handler,
        .user_data = e->user_data,
    };

    e->event_system->count++;

    return true;
}

static bool on_unsubscribe_event(const ___unsubscribe_event_t *e, void *user_data)
{
    event_system_entry_t *entries = e->event_system->entries;
    const size_t count = e->event_system->count;

    for (size_t i = first_index_of(e->event_system, e->type); i < count && strcmp(entries[i].type, e->type) == 0; i++)
        if (e->handler == entries[i].handler && e->user_data == entries[i].user_data)
        {
            if (count - i != 1)
                memmove(&entries[i], &entries[i + 1], (count - i) * sizeof(event_system_entry_t));

            e->event_system->count--;

            break;
        }

    return true;
}

event_system_t *event_system_global()
{
    if (g_event_system)
        return g_event_system;

    g_event_system = event_system_create();

    return g_event_system;
}

event_system_t *event_system_create()
{
    event_system_t *event_system = lv_malloc(sizeof(event_system_t));

    *event_system = (event_system_t){
        .capacity = DEFAULT_ENTRY_CAPACITY,
        .count = 0,
        .entries = lv_malloc(DEFAULT_ENTRY_CAPACITY * sizeof(event_system_entry_t)),
        .async = {
            .capacity = DEFAULT_ASYNC_CAPACITY,
            .size = 0,
            .events = lv_malloc(DEFAULT_ASYNC_CAPACITY),
        },
        .is_locked = false,
    };

    event_system_subscribe_to(event_system, ___subscribe_event_t, on_subscribe_event, NULL);
    event_system_subscribe_to(event_system, ___unsubscribe_event_t, on_unsubscribe_event, NULL);

    return event_system;
}

void event_system_delete(event_system_t *event_system)
{
    assert(!event_system->is_locked);

    while (_event_system_dispatch_async_events(event_system))
        ;

    event_system_unsubscribe_from(event_system, ___unsubscribe_event_t, on_unsubscribe_event, NULL);
    event_system_unsubscribe_from(event_system, ___subscribe_event_t, on_subscribe_event, NULL);

    lv_free(event_system->async.events);
    lv_free(event_system->entries);
    lv_free(event_system);

    if (event_system == g_event_system)
        g_event_system = NULL;
}

void _event_system_subscribe(event_system_t *event_system, const char *type, event_system_handler_t handler, void *user_data)
{
    const ___subscribe_event_t e = {
        .event_system = event_system,
        .type = type,
        .handler = handler,
        .user_data = user_data,
    };

    if (event_system->is_locked)
        event_system_dispatch_async_to(event_system, ___subscribe_event_t, &e);
    else
        on_subscribe_event(&e, NULL);
}

void _event_system_unsubscribe(event_system_t *event_system, const char *type, event_system_handler_t handler, void *user_data)
{
    const ___unsubscribe_event_t e = {
        .event_system = event_system,
        .type = type,
        .handler = handler,
        .user_data = user_data,
    };

    if (event_system->is_locked)
        event_system_dispatch_async_to(event_system, ___unsubscribe_event_t, &e);
    else
        on_unsubscribe_event(&e, NULL);
}

bool _event_system_dispatch(event_system_t *event_system, const char *type, const void *event)
{
    const event_system_entry_t *entries = event_system->entries;
    const size_t count = event_system->count;

    bool locked_by_this = false;

    if (!event_system->is_locked)
    {
        event_system->is_locked = true;

        locked_by_this = true;
    }

    bool dispatched = false;

    for (size_t i = first_index_of(event_system, type); i < count && strcmp(entries[i].type, type) == 0; i++)
    {
        dispatched = true;

        if (!entries[i].handler(event, entries[i].user_data))
            break;
    }

    if (locked_by_this)
        event_system->is_locked = false;

    return dispatched;
}

void _event_system_dispatch_async(event_system_t *event_system, const char *type, const void *event, const size_t size)
{
    const size_t size_full = sizeof(event_system_async_event_t) + size;
    const size_t alignment = sizeof(void *);
    const size_t size_aligned = (size_full + alignment - 1) & ~(alignment - 1);
    const size_t capacity = event_system->async.capacity;
    const size_t size_used = event_system->async.size;
    const size_t available = capacity - size_used;

    if (available < size_aligned)
    {
        const size_t new_capacity = capacity + _max(capacity / 2, size_aligned);

        event_system->async.events = lv_realloc(event_system->async.events, new_capacity);
        event_system->async.capacity = new_capacity;
    }

    event_system_async_event_t *async_event = (event_system_async_event_t *)&event_system->async.events[size_used];

    *async_event = (event_system_async_event_t){
        .type = type,
        .stride = size_aligned,
    };

    memcpy(async_event->data, event, size);

    event_system->async.size += size_aligned;
}

bool _event_system_dispatch_async_events(event_system_t *event_system)
{
    assert(!event_system->is_locked);

    const size_t size = event_system->async.size;

    if (!size)
        return false;

    size_t handled = 0;
    bool dispatched = false;

    while (handled < size)
    {
        event_system_async_event_t *event = (event_system_async_event_t *)&event_system->async.events[handled];

        const size_t stride = event->stride;

        dispatched |= _event_system_dispatch(event_system, event->type, event->data);

        handled += stride;
    }

    assert(handled == size);

    const size_t new_size = event_system->async.size;

    if (new_size != size)
    {
        memmove(event_system->async.events, event_system->async.events + handled, new_size - size);

        event_system->async.size -= handled;
    }
    else
        event_system->async.size = 0;

    return dispatched;
}
