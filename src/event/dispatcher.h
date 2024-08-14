#pragma once

#include <algorithm>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "event/event.h"

namespace event
{
    class dispatcher
    {
    public:
        using handler_type = std::function<bool(const event &)>;
        using handler_id = size_t;

        static dispatcher &global()
        {
            return s_dispatcher;
        }

        template <typename E>
        handler_id subscribe(handler_type handler)
        {
            m_handlers[std::type_index(typeid(E))].push_back({m_handler_id, handler});

            return m_handler_id++;
        }

        void unsubscribe(handler_id id)
        {
            for (auto &[_, handlers] : m_handlers)
            {
                auto predicate = [id](const auto &handler)
                {
                    return std::get<0>(handler) == id;
                };

                handlers.erase(std::remove_if(handlers.begin(), handlers.end(), predicate), handlers.end());
            }
        }

        template <typename E>
        void dispatch(const E &event)
        {
            auto handlers = m_handlers.find(std::type_index(typeid(E)));

            if (handlers != m_handlers.end())
                for (auto &[_, handler] : handlers->second)
                    if (!handler(event))
                        break;
        }

    private:
        static dispatcher s_dispatcher;

        std::unordered_map<std::type_index, std::vector<std::tuple<handler_id, handler_type>>> m_handlers;
        handler_id m_handler_id = 0;
    };
}