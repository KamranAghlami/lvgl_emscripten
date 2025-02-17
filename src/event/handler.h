#pragma once

#include <cassert>
#include <vector>

#include "event/dispatcher.h"
#include "driver/memory.h"

namespace event
{
    template <typename T>
    class handler
    {
    public:
        using handler_type = dispatcher::handler_type;
        using subscription_id = dispatcher::subscription_id;

        handler(dispatcher &d = dispatcher::global()) : m_dispatcher(d)
        {
        }

        virtual ~handler()
        {
            for (const auto &id : m_subscription_ids)
                unsubscribe(id);
        };

    protected:
        template <typename C, typename E>
        subscription_id subscribe(bool (C::*handler)(const E &))
        {
            handler_type proxy = [this, handler](const event &e) -> bool
            {
                auto t_ptr = dynamic_cast<T *>(this);

                assert(t_ptr);

                return (t_ptr->*handler)(static_cast<const E &>(e));
            };

            m_subscription_ids.push_back(m_dispatcher.subscribe<E>(proxy));

            return m_subscription_ids.back();
        }

        void unsubscribe(subscription_id id)
        {
            m_dispatcher.unsubscribe(id);
        }

    private:
        dispatcher &m_dispatcher;
        driver::memory::vector<subscription_id> m_subscription_ids;
    };
}