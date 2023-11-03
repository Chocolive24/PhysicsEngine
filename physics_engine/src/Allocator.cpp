//
// Created by Olivier on 31.10.2023.
//

#include "Allocator.h"

namespace PhysicsEngine
{
    void* HeapAllocator::Allocate(std::size_t allocationSize, std::size_t alignment)
    {
        if (allocationSize == 0)
        {
            return nullptr;
        }

        const auto size = allocationSize * alignment;
        auto* ptr = std::malloc(size);

    #ifdef TRACY_ENABLE
            TracyAlloc(ptr, size);
    #endif

        return ptr;
    }

    void HeapAllocator::Deallocate(void* ptr)
    {
    #ifdef TRACY_ENABLE
            TracyFree(ptr);
    #endif

        std::free(ptr);
    }

    //void* LinearAllocator::Allocate(std::size_t allocationSize, std::size_t alignment)
    //{
    //    const auto adjustment = MemoryAlignment::CalculateAlignForwardAdjustment(_currentPosPtr,
    //                                                                             alignment);

    //    // Check if the allocation will exceed the allocator size.
    //    if(_usedMemory + adjustment + allocationSize > _size)
    //    {
    //        return nullptr;
    //    }

    //    void* alignedAddress = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(_currentPosPtr) + adjustment);
    //    _currentPosPtr = reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(alignedAddress) + allocationSize);

    //    _usedMemory += allocationSize + adjustment;
    //    _allocationCount++;

    //    return alignedAddress;
    //}

    //void LinearAllocator::Deallocate(void *ptr)
    //{
    //    // Linear allocator cannot deallocate memory.
    //}

    //void LinearAllocator::Clear() noexcept
    //{
    //    _currentPosPtr = _rootPtr;
    //    _size = 0;
    //    _usedMemory = 0;
    //    _allocationCount = 0;
    //}

    //void* ProxyAllocator::Allocate(std::size_t size, std::size_t alignment) noexcept
    //{
    //    _allocationCount++;
    //    size_t usedMemory = _allocator.UsedMemory();

    //    void* ptr = _allocator.Allocate(size, alignment);
    //    _usedMemory += _allocator.UsedMemory() - usedMemory;

    //    return ptr;
    //}

    //void ProxyAllocator::Deallocate(void* ptr) noexcept
    //{
    //    _allocationCount--;
    //    size_t mem = _allocator.UsedMemory();
    //    _allocator.Deallocate(ptr);
    //    _usedMemory -= mem - _allocator.UsedMemory();
    //}

    //namespace MemoryAlignment
    //{
    //    std::size_t CalculateAlignForwardAdjustment(const void* address, std::size_t alignment)
    //    {
    //        const std::size_t adjustment = alignment - (reinterpret_cast<std::uintptr_t>(address) & (alignment - 1));

    //        //already aligned.
    //        if(adjustment == alignment) return 0;

    //        return adjustment;
    //    }
    //}
}