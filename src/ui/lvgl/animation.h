#pragma once

extern "C"
{
    struct lv_anim_t;
}

namespace ui
{
    namespace lvgl
    {
        class animation
        {
        public:
            animation() {}
            ~animation() {}

            animation(const animation &) = delete;
            animation(animation &&) = delete;
            animation &operator=(const animation &) = delete;
            animation &operator=(animation &&) = delete;

            lv_anim_t *lv_animation() const;

        private:
            lv_anim_t *mp_animation;
        };
    }
}
