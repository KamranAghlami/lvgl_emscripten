#include "application/application.h"

#include "ui/screens/main.h"

class example : public application
{
public:
    example()
    {
    }

    ~example()
    {
    }

private:
    void on_ready() override
    {
        m_main.load();
    };

    ui::screens::main m_main;
};

DEFINE_MAIN(example);
