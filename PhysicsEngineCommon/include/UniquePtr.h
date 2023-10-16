#pragma once

template<typename T>
class UniquePtr
{
private:
    T* _ptr = nullptr;

public:
    constexpr explicit UniquePtr() noexcept = default;
    constexpr explicit UniquePtr(T* ptr) noexcept : _ptr(ptr) {};
    constexpr UniquePtr(const UniquePtr& other) noexcept = delete;

    ~UniquePtr() noexcept { delete _ptr; }

    constexpr UniquePtr& operator=(UniquePtr&& other) const noexcept = delete;
    constexpr UniquePtr& operator=(const UniquePtr& other) const noexcept = delete;

    constexpr T& operator*() const noexcept { return *_ptr; }
    constexpr T* operator->() const noexcept { return _ptr; }

    [[nodiscard]] constexpr T* Get() const noexcept { return _ptr; }
};