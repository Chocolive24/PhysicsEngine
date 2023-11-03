#pragma once

#ifdef TRACY_ENABLE
#include <Tracy.hpp>
#endif // TRACY_ENABLE

#include <cstddef>
#include <memory>
#include <vector>

namespace PhysicsEngine
{

    /**
     * @class Allocator is an abstract class the defines the fundamental elements shared between all different custom
     * allocators. It also enabled to see and analise the number of allocations made and the amount of memory used.
     */
    class Allocator
    {
    protected:
        void* _rootPtr = nullptr;
        std::size_t _size = 0;
        std::size_t _usedMemory = 0;
        std::size_t _allocationCount = 0;

    public:
        Allocator() noexcept = default;
        Allocator(void* rootPtr, std::size_t size) noexcept
        {
            _rootPtr = rootPtr;
            _size = size;
            _usedMemory = 0;
            _allocationCount = 0;
        }

        virtual ~Allocator() noexcept
        {
            _rootPtr = nullptr;
            _size = 0;
            _usedMemory = 0;
            _allocationCount = 0;
        };

        /**
         * @brief Allocate is a method that allocates a given amount of memory.
         * @param allocationSize The size of the allocation to do.
         * @param alignment The alignment in memory of the allocation.
         * @return A pointer pointing to the memory (aka a void*).
         */
        virtual void* Allocate(std::size_t allocationSize, std::size_t alignment) = 0;

        /**
         * @brief Deallocate is a method that deallocates a block of memory given in parameter.
         * @param ptr The pointer to the memory block to deallocates.
         */
        virtual void Deallocate(void* ptr) = 0;

        /**
         * @brief RootPtr is a method that gives to root pointer of the allocator (aka the start of the memory block of
         * the allocator).
         * @return The root pointer of the allocator.
         */
        [[nodiscard]] void* RootPtr() const noexcept { return _rootPtr; }

        /**
         * @brief Size is a method that gives to size of the block of memory of the allocator.
         * @return The size of the block of memory of the allocator.
         */
        [[nodiscard]] std::size_t Size() const noexcept { return _size; }

        /**
         * @brief UseMemory is a method that gives the amount of memory used with the allocator.
         * @return The amount of memory used with the allocator.
         */
        [[nodiscard]] std::size_t UsedMemory() const noexcept { return _usedMemory; }

        /**
         * @brief AllocationCount is a method that gives the count of allocation made with the allocator.
         * @return The count of allocation made with the allocator..
         */
        [[nodiscard]] std::size_t AllocationCount() const noexcept { return _allocationCount; }
    };

    class HeapAllocator final : public Allocator
    {
    public:
        /**
         * @brief Allocate is a method that allocates a given amount of memory.
         * @param allocationSize The size of the allocation to do.
         * @param alignment The alignment in memory of the allocation.
         * @return A pointer pointing to the memory (aka a void*).
         */
        void* Allocate(std::size_t allocationSize, std::size_t alignment) override;

        /**
         * @brief Deallocate is a method that deallocates a block of memory given in parameter.
         * @param ptr The pointer to the memory block to deallocates.
         */
        void Deallocate(void* ptr) override;
    };

    /**
     * @class LinearAllocator is a class that defines a linear allocator (aka an allocator that allocates memory block
     * one after the other).
     */
    class LinearAllocator final : public Allocator
    {
    private:
        void* _currentPosPtr = nullptr;

    public:
        LinearAllocator() noexcept = default;
        LinearAllocator(void* rootPtr, std::size_t size) : Allocator(rootPtr, size), _currentPosPtr(rootPtr) {};

        ~LinearAllocator() override { _currentPosPtr = nullptr; }

        /**
         * @brief Allocate is a method that allocates a given amount of memory.
         * @param allocationSize The size of the allocation to do.
         * @param alignment The alignment in memory of the allocation.
         * @return A pointer pointing to the memory (aka a void*).
         */
        void* Allocate(std::size_t allocationSize, std::size_t alignment) override;

        /**
         * @brief Deallocate is a method that deallocates a block of memory given in parameter.
         * @param ptr The pointer to the memory block to deallocates.
         */
        void Deallocate(void* ptr) override;

        /**
         * @brief Clear is a method that reset the allocator to its start state (aka it sets the currentPosPtr to
         * the rootPtr, sets the size to 0 and reset memory values to 0).
         */
        void Clear() noexcept;
    };

    /**
     * @class LinearAllocator is a class that defines a proxy allocator (aka an allocator that redirects all
     * allocations/deallocations to the an intern allocator).
     */
    class ProxyAllocator final : public Allocator
    {
    private:
        Allocator& _allocator;

    public:
        explicit ProxyAllocator(Allocator& allocator) noexcept : _allocator(allocator) {};
        ~ProxyAllocator() override = default;

        /**
         * @brief Allocate is a method that allocates a given amount of memory.
         * @param allocationSize The size of the allocation to do.
         * @param alignment The alignment in memory of the allocation.
         * @return A pointer pointing to the memory (aka a void*).
         */
        [[nodiscard]] void* Allocate(std::size_t size, std::size_t alignment) noexcept override;

        /**
         * @brief Deallocate is a method that deallocates a block of memory given in parameter.
         * @param ptr The pointer to the memory block to deallocates.
         */
        void Deallocate(void* ptr) noexcept override;
    };

    /**
     * @namespace MemoryAlignment is a namespace that contains useful functions for calculating memory alignments
     * for allocations.
     */
    namespace MemoryAlignment
    {
        /**
         * @brief CalculateAlignForwardAdjustment is a method that calculates the adjustment to apply to the memory
         * address to match the alignment in memory given in parameter.
         * @param address The address to align in memory.
         * @param alignment The alignment in memory.
         * @return The adjustment to apply to the memory address to match the alignment.
         */
        std::size_t CalculateAlignForwardAdjustment(const void* address, std::size_t alignment);
    }

    /**
     * \brief Custom proxy allocator respecting _allocatortraits
     */
    template<typename T>
    class StandardAllocator
    {
    public:
        typedef T value_type;
        StandardAllocator(Allocator& allocator);
        template <class U>
        StandardAllocator(const StandardAllocator<U>& allocator) noexcept : _allocator(allocator.GetAllocator()) {}
        T* allocate(std::size_t n);
        void deallocate(T* ptr, std::size_t n);
        [[nodiscard]] Allocator& GetAllocator() const { return _allocator; }
    protected:
        Allocator& _allocator;
    };


    template <class T, class U>
    constexpr bool operator== (const StandardAllocator<T>&, const StandardAllocator<U>&) noexcept
    {
        return true;
    }

    template <class T, class U>
    constexpr bool operator!= (const StandardAllocator<T>&, const StandardAllocator<U>&) noexcept
    {
        return false;
    }

    template <typename T>
    StandardAllocator<T>::StandardAllocator(Allocator& allocator) : _allocator(allocator)
    {
    }

    template <typename T>
    T* StandardAllocator<T>::allocate(std::size_t n)
    {
        return static_cast<T*>(_allocator.Allocate(n * sizeof(T), alignof(T)));
    }

    template <typename T>
    void StandardAllocator<T>::deallocate(T* ptr, std::size_t n)
    {
        _allocator.Deallocate(ptr);
    }

    template<typename T>
    using AllocVector = std::vector<T, StandardAllocator<T>>;
}