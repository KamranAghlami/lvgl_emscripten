#pragma once

#include <cstdint>

namespace ui
{
    namespace lvgl
    {
        class color24
        {
        public:
            enum class format
            {
                UNKNOWN = 0,
                RAW = 0x01,
                RAW_ALPHA = 0x02,
                L8 = 0x06,
                I1 = 0x07,
                I2 = 0x08,
                I4 = 0x09,
                I8 = 0x0A,
                A8 = 0x0E,
                RGB565 = 0x12,
                ARGB8565 = 0x13,
                RGB565A8 = 0x14,
                AL88 = 0x15,
                RGB888 = 0x0F,
                ARGB8888 = 0x10,
                XRGB8888 = 0x11,
                A1 = 0x0B,
                A2 = 0x0C,
                A4 = 0x0D,
                YUV_START = 0x20,
                I420 = YUV_START,
                I422 = 0x21,
                I444 = 0x22,
                I400 = 0x23,
                NV21 = 0x24,
                NV12 = 0x25,
                YUY2 = 0x26,
                UYVY = 0x27,
                YUV_END = UYVY,
            };

            static color24 random();

            color24() : m_red(0), m_green(0), m_blue(0) {}
            color24(uint8_t red, uint8_t green, uint8_t blue) : m_red(red), m_green(green), m_blue(blue) {}

            uint8_t red() const { return m_red; }
            uint8_t green() const { return m_green; }
            uint8_t blue() const { return m_blue; }

            color24 darkened(uint8_t v) const;
            color24 negative() const;

        protected:
            uint8_t m_red;
            uint8_t m_green;
            uint8_t m_blue;
        };

        class color32 : public color24
        {
        public:
            color32() : m_alpha(0xff) {}
            color32(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xff) : color24(red, green, blue), m_alpha(alpha) {}

            uint8_t alpha() const { return m_alpha; }

        private:
            uint8_t m_alpha;
        };

        using color = color24;
    }
}