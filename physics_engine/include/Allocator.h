#pragma once

#include <cstddef>

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

    class LinearAllocator final : public Allocator
    {
    private:
        void* _currentPosPtr = nullptr;

    public:
        LinearAllocator() noexcept = default;
        LinearAllocator(void* rootPtr, std::size_t size) : Allocator(rootPtr, size), _currentPosPtr(rootPtr) {};

        ~LinearAllocator() override { _currentPosPtr = nullptr; }

        void* Allocate(std::size_t allocationSize, std::size_t alignment) override;
        void Deallocate(void* ptr) override;

        void Clear() noexcept;
    };

    class ProxyAllocator final : public Allocator
    {
    private:
        Allocator& _allocator;

    public:
        explicit ProxyAllocator(Allocator& allocator) noexcept : _allocator(allocator) {};
        ~ProxyAllocator() override = default;

        [[nodiscard]] void* Allocate(std::size_t size, std::size_t alignment) noexcept override;
        void Deallocate(void* ptr) noexcept override;
    };

/**
 * @namespace MemoryAlignment is a namespace that contains useful functions for calculating memory alignments
 * for allocations.
 */
    namespace MemoryAlignment
    {
        std::size_t CalculateAlignForwardAdjustment(const void* address, std::size_t alignment);
    }
}