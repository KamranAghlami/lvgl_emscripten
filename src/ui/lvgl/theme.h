#pragma once

extern "C"
{
    struct lv_theme_t;
    struct lv_obj_t;
}

namespace ui
{
    namespace lvgl
    {
        class theme
        {
        public:
            theme();
            virtual ~theme();

            theme(const theme &) = delete;
            theme(theme &&) = delete;
            theme &operator=(const theme &) = delete;
            theme &operator=(theme &&) = delete;

            void activate();

            lv_theme_t *lv_theme();

        protected:
            virtual void apply_callback(lv_theme_t *t, lv_obj_t *o) = 0;

        private:
            lv_theme_t *mp_theme;
        };
    }
}
