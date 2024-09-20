#pragma once

#include <limits>
#include <new>

namespace ui
{
    namespace lvgl
    {
        void *malloc(size_t size);
        void free(void *data);

        template <class T>
        struct allocator
        {
            typedef T value_type;

            allocator() = default;

            template <class U>
            constexpr allocator(const allocator<U> &) noexcept {}

            [[nodiscard]] T *allocate(std::size_t n)
            {
                if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
                    throw std::bad_array_new_length();

                if (auto p = static_cast<T *>(lvgl::malloc(n * sizeof(T))))
                    return p;

                throw std::bad_alloc();
            }

            void deallocate(T *p, std::size_t n) noexcept
            {
                lvgl::free(p);
            }
        };

        template <class T, class U>
        bool operator==(const allocator<T> &, const allocator<U> &) { return true; }

        template <class T, class U>
        bool operator!=(const allocator<T> &, const allocator<U> &) { return false; }
    }
}
