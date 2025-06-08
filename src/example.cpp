#include "application/application.h"

#include "ui/screens/main.h"

class example : public application
{
public:
    example() : mp_screen(ui::screens::main::create())
    {
    }

    ~example()
    {
        if (lv_screen_active() != mp_screen)
            lv_obj_delete(mp_screen);
    }

private:
    void on_ready() override
    {
        lv_screen_load(mp_screen);
    };

    lv_obj_t *mp_screen = nullptr;
};

DEFINE_MAIN(example);
