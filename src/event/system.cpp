#include <event/system.h>

namespace event
{
    system &system::global()
    {
        static system g_system(event_system_global());

        return g_system;
    }
}