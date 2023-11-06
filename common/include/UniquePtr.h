#pragma once

/**
 * @headerfile UniquePtr.h
 * This file defines the UniquePtr class which is a naive implementation of the std::unique_ptr standard library class.
 *
 * @author Olivier Pachoud
 */

#include <algorithm>

template<typename T>
class UniquePtr
{
private:
    T* _ptr = nullptr;

public:
    constexpr explicit UniquePtr() noexcept = default;

    constexpr explicit UniquePtr(T *ptr) noexcept: _ptr(ptr) {};

    constexpr UniquePtr(const UniquePtr<T>& other) noexcept = delete;

    constexpr UniquePtr(UniquePtr<T>&& other) noexcept
    {
        std::swap(_ptr, other._ptr);
    }

    ~UniquePtr() noexcept { delete _ptr; }

    constexpr UniquePtr& operator=(const UniquePtr<T>& other) const noexcept = delete;

    constexpr UniquePtr& operator=(UniquePtr<T>&& other) noexcept
    {
        std::swap(_ptr, other._ptr);
        return *this;
    }

    [[nodiscard]] constexpr T& operator*() const noexcept { return *_ptr; }
    [[nodiscard]] constexpr T* operator->() const noexcept { return _ptr; }

    template<typename U>
    explicit constexpr operator UniquePtr<U>() noexcept
    {
        auto ptrToCast = _ptr;
        _ptr = nullptr;

        return UniquePtr<U>(ptrToCast);
    }

    /**
     * @brief Get is a method that gives the pointer inside the unique pointer object.
     * @param value The value to point with the unique pointer.
     * @return The pointer inside the unique pointer object.
     */
    [[nodiscard]] constexpr T* Get() const noexcept { return _ptr; }
};

/**
* @brief MakeUnique is a method that creates a unique pointer of the type of the value in parameter.
* @param value The value to point with the unique pointer.
* @return The unique pointer object that points the value.
*/
template<typename T>
[[nodiscard]] UniquePtr<T> MakeUnique(const T& value) noexcept
{
    return UniquePtr<T>(new T(value));
}

/**
 * @brief MakeUnique is a method that creates a unique pointer of the type of the value in parameter.
 * @param value The value to point with the unique pointer.
 * @return The unique pointer object that points the value.
 */
template<typename T, typename U>
[[nodiscard]] UniquePtr<T> MakeUnique(const U& value) noexcept
{
    return UniquePtr<T>(new U(value));
}