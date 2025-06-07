#include "application/application.h"

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
    void on_ready() override {
    };
};

DEFINE_MAIN(example);
