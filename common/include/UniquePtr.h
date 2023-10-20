#pragma once

/**
 * @headerfile UniquePtr class is a naive implementation of the std::unique_ptr standard library class.
 * @author Olivier
 */

#include <algorithm>

template<typename T>
class UniquePtr
{
private:
    T *_ptr = nullptr;

public:
    constexpr explicit UniquePtr() noexcept = default;

    constexpr explicit UniquePtr(T *ptr) noexcept: _ptr(ptr) {};

    constexpr UniquePtr(const UniquePtr<T> &other) noexcept = delete;

    constexpr UniquePtr(UniquePtr<T> &&other) noexcept
    {
        std::swap(_ptr, other._ptr);
    }

    ~UniquePtr() noexcept { delete _ptr; }

    constexpr UniquePtr &operator=(const UniquePtr<T> &other) const noexcept = delete;

    constexpr UniquePtr &operator=(UniquePtr<T> &&other) noexcept
    {
        std::swap(_ptr, other._ptr);
        return *this;
    }

    [[nodiscard]] constexpr T &operator*() const noexcept { return *_ptr; }
    [[nodiscard]] constexpr T *operator->() const noexcept { return _ptr; }

    /**
     * @brief Implicit conversion operator to convert a UniquePtr to a UniquePtr of a different type.
     * @param The target type of the conversion.
     * @return A UniquePtr of the specified target type.
     */
    template<typename U>
    explicit constexpr operator UniquePtr<U>() const noexcept
    {
        auto ptrToCast = _ptr;
        _ptr = nullptr;

        return UniquePtr<U>(ptrToCast);
    }

    [[nodiscard]] static constexpr UniquePtr<T> MakeUnique(T value) noexcept
    {
        return UniquePtr<T>(new T(value));
    }

    [[nodiscard]] constexpr T *Get() const noexcept { return _ptr; }
};
