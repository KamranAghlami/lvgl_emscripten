#pragma once

#include <cassert>
#include <vector>

#include "event/dispatcher.h"

namespace event
{
    template <typename T>
    class handler
    {
    public:
        handler(dispatcher &d = dispatcher::global()) : m_dispatcher(d)
        {
        }

        virtual ~handler()
        {
            for (const auto &id : m_handler_ids)
                m_dispatcher.unsubscribe(id);
        };

    protected:
        template <typename C, typename E>
        void subscribe(bool (C::*handler)(const E &))
        {
            dispatcher::handler_type proxy = [this, handler](const event &e) -> bool
            {
                auto t_ptr = dynamic_cast<T *>(this);

                assert(t_ptr);

                return (t_ptr->*handler)(static_cast<const E &>(e));
            };

            m_handler_ids.push_back(m_dispatcher.subscribe<E>(proxy));
        }

    private:
        dispatcher &m_dispatcher;
        std::vector<dispatcher::handler_id> m_handler_ids;
    };
}