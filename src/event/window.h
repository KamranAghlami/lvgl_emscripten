#pragma once

#include "event/event.h"

namespace event
{
    namespace window
    {
        class size_changed : public event
        {
        public:
            size_changed(const int width, const int height)
                : m_width(width),
                  m_height(height)
            {
            }

            const int m_width;
            const int m_height;
        };
    }
}