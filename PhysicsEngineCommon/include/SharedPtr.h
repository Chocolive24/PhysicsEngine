#pragma once

template<typename T>
class SharedPtr
{
private:
    T* _ptr = nullptr;
    int* _count = nullptr;

public:
    constexpr explicit SharedPtr() noexcept = default;
    constexpr explicit SharedPtr(T* ptr) noexcept : _ptr(ptr), _count(new int(1)) {};

    constexpr SharedPtr(const SharedPtr& other) noexcept
    {
        _ptr = other._ptr;
        _count = other._count;

        (*_count)++;
    }

    constexpr SharedPtr(SharedPtr&& other) noexcept
    {
        _ptr = other._ptr;
        _count = other._count;

        other._ptr = nullptr;
        other._count = nullptr;
    }

    ~SharedPtr() noexcept
    {
        if ((*_count) == 1)
        {
            delete _ptr;
            delete _count;
        }
    }

    constexpr T& operator*() const noexcept { return *_ptr; }
    constexpr T* operator->() const noexcept { return _ptr; }

    [[nodiscard]] constexpr T* Get() const noexcept { return _ptr; }
    [[nodiscard]] constexpr int SharedCount() const noexcept { return *_count; }
};