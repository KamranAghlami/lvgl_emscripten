#pragma once

#include <limits>
#include <list>
#include <memory>
#include <new>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace lvgl
{
    void *malloc(size_t size);
    void free(void *data);
    void memset(void *buffer, uint8_t value, size_t length);

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

    template <typename T>
    using basic_string = std::basic_string<T, std::char_traits<T>, allocator<T>>;

    using string = basic_string<char>;

    template <typename T>
    using basic_ostringstream = std::basic_ostringstream<T, std::char_traits<T>, allocator<T>>;

    using ostringstream = basic_ostringstream<char>;

    template <typename T>
    using vector = std::vector<T, allocator<T>>;

    template <typename T>
    using list = std::list<T, allocator<T>>;

    template <typename K, typename V>
    using unordered_map = std::unordered_map<K, V, std::hash<K>, std::equal_to<K>, allocator<std::pair<K const, V>>>;

    template <typename K, typename V>
    using unordered_multimap = std::unordered_multimap<K, V, std::hash<K>, std::equal_to<K>, allocator<std::pair<K const, V>>>;

    template <typename T>
    struct default_delete
    {
        default_delete() = default;

        template <typename U>
        constexpr default_delete(const default_delete<U> &) noexcept {}

        void operator()(T *ptr) const noexcept
        {
            static_assert(sizeof(T) >= 0, "cannot delete an incomplete type");
            static_assert(!std::is_void_v<T>, "cannot delete an incomplete type");

            ptr->~T();

            free(ptr);
        }
    };

    template <typename T>
    using unique_ptr = std::unique_ptr<T, default_delete<T>>;

    template <typename T, typename... Args>
    unique_ptr<T> make_unique(Args &&...args)
    {
        auto mem = malloc(sizeof(T));

        if (!mem)
            throw std::bad_alloc();

        try
        {
            return unique_ptr<T>(new (mem) T(std::forward<Args>(args)...));
        }
        catch (...)
        {
            free(mem);

            throw;
        }
    }
}
