#pragma once

/**
 * @headerfile SharedPtr class is basic reimplementation of the std::shared_ptr standard library class.
 * @author Olivier
 */

namespace PhysicsEngine
{
    template<typename T>
    class SharedPtr
    {
    private:
        T* _ptr = nullptr;
        int* _count = nullptr;

    public:
        constexpr explicit SharedPtr() noexcept = default;
        constexpr explicit SharedPtr(T* ptr) noexcept : _ptr(ptr), _count(new int(1)) {};

        constexpr SharedPtr(const SharedPtr<T>& other) noexcept : _ptr(other._ptr), _count(other._count)
        {
            (*_count)++;
        }

        constexpr SharedPtr(SharedPtr<T>&& other) noexcept : _ptr(other._ptr), _count(other._count)
        {
            other._ptr = nullptr;
            other._count = nullptr;
        }

        ~SharedPtr() noexcept
        {
            (*_count)--;

            if ((*_count) == 0)
            {
                delete _ptr;
                delete _count;
            }
        }

        constexpr SharedPtr<T>& operator=(const SharedPtr<T>& other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            _ptr = other._ptr;
            _count = other._count;

            (*_count)++;

            return *this;
        }

        constexpr SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept
        {
            _ptr = other._ptr;
            _count = other._count;

            other._ptr = nullptr;
            other._count = nullptr;

            return *this;
        }

        [[nodiscard]] constexpr T& operator*() const noexcept { return *_ptr; }
        [[nodiscard]] constexpr T* operator->() const noexcept { return _ptr; }

        [[nodiscard]] constexpr T* Get() const noexcept { return _ptr; }
        [[nodiscard]] constexpr int SharedCount() const noexcept { return *_count; }
    };
}