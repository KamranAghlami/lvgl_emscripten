#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "event/extensions.h"

#define event_system_subscribe_to(es, T, h, ud) _event_system_subscribe(es, #T, (event_system_handler_t)h, ud)
#define event_system_subscribe(T, h, ud) event_system_subscribe_to(event_system_global(), T, h, ud)
#define event_system_unsubscribe_from(es, T, h, ud) _event_system_unsubscribe(es, #T, (event_system_handler_t)h, ud)
#define event_system_unsubscribe(T, h, ud) event_system_unsubscribe_from(event_system_global(), T, h, ud)
#define event_system_dispatch_to(es, T, e) _event_system_dispatch(es, #T, (const void *)e)
#define event_system_dispatch(T, e) event_system_dispatch_to(event_system_global(), T, e)
#define event_system_dispatch_async_to(es, T, e) _event_system_dispatch_async(es, #T, (const void *)e, sizeof(T))
#define event_system_dispatch_async(T, e) event_system_dispatch_async_to(event_system_global(), T, e)
#define event_system_dispatch_async_events_in(es) _event_system_dispatch_async_events(es)
#define event_system_dispatch_async_events() event_system_dispatch_async_events_in(event_system_global())

    typedef bool (*event_system_handler_t)(const void *event, void *user_data);
    typedef struct event_system_st event_system_t;

    event_system_t *event_system_global();

    event_system_t *event_system_create();
    void event_system_delete(event_system_t *event_system);

    void _event_system_subscribe(event_system_t *event_system, const char *type, event_system_handler_t handler, void *user_data);
    void _event_system_unsubscribe(event_system_t *event_system, const char *type, event_system_handler_t handler, void *user_data);
    bool _event_system_dispatch(event_system_t *event_system, const char *type, const void *event);
    void _event_system_dispatch_async(event_system_t *event_system, const char *type, const void *event, const size_t size);
    bool _event_system_dispatch_async_events(event_system_t *event_system);

#ifdef __cplusplus
}

#include <typeinfo>

namespace event
{
    class system
    {
    public:
        template <typename T>
        using handler = bool (*)(const T *, void *);

        static system &global();

        system() : system(event_system_create())
        {
        }

        ~system()
        {
            event_system_delete(m_system);
        }

        system(const system &) = delete;
        system(system &&) = delete;
        system &operator=(const system &) = delete;
        system &operator=(system &&) = delete;

        template <typename T>
        void subscribe(handler<T> h, void *user_data = nullptr)
        {
            _event_system_subscribe(m_system, typeid(T).name(), reinterpret_cast<event_system_handler_t>(h), user_data);
        }

        template <typename T>
        void unsubscribe(handler<T> h, void *user_data = nullptr)
        {
            _event_system_unsubscribe(m_system, typeid(T).name(), reinterpret_cast<event_system_handler_t>(h), user_data);
        }

        template <typename T>
        bool dispatch(const T &e)
        {
            return _event_system_dispatch(m_system, typeid(T).name(), static_cast<const void *>(&e));
        }

        template <typename T>
        void dispatch_async(const T &e)
        {
            _event_system_dispatch_async(m_system, typeid(T).name(), static_cast<const void *>(&e), sizeof(T));
        }

        bool dispatch_async_events()
        {
            return _event_system_dispatch_async_events(m_system);
        }

    private:
        system(event_system_t *system) : m_system(system)
        {
        }

        event_system_t *m_system;
    };
}
#endif

#endif
