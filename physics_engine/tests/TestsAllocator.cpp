#include "Allocator.h"

#include "gtest/gtest.h"

using namespace PhysicsEngine;

struct AllocationSizeFixture : public ::testing::TestWithParam<int> {};

struct AllocationSizeAndAlignmentFixture : public ::testing::TestWithParam<std::pair<int, int>> {};

INSTANTIATE_TEST_SUITE_P(Allocator, AllocationSizeFixture, testing::Values(
        0, 10, 50, 100, 1000, 3456, -10
        ));

INSTANTIATE_TEST_SUITE_P(Allocator, AllocationSizeAndAlignmentFixture, testing::Values(
        std::pair{10, 4},
        std::pair{10, 8},
        std::pair{100, 8}
));

TEST(LinearAllocator, DefaultConstructor)
{
    LinearAllocator linearAllocator;

    EXPECT_EQ(linearAllocator.RootPtr(), nullptr);
    EXPECT_EQ(linearAllocator.Size(), 0);
    EXPECT_EQ(linearAllocator.UsedMemory(), 0);
    EXPECT_EQ(linearAllocator.AllocationCount(), 0);
}

TEST_P(AllocationSizeFixture, LinearAllocatorConstructor)
{
    const auto size = GetParam();
    void* ptr = std::malloc(size);

    LinearAllocator linearAllocator(ptr, size);

    EXPECT_EQ(linearAllocator.RootPtr(), ptr);
    EXPECT_EQ(linearAllocator.Size(), size);
    EXPECT_EQ(linearAllocator.UsedMemory(), 0);
    EXPECT_EQ(linearAllocator.AllocationCount(), 0);

    std::free(ptr);
}

TEST_P(AllocationSizeAndAlignmentFixture, LinearAllocate)
{
    auto [size, align] = GetParam();

    void* ptr = std::malloc(10000); // 10000 is the allocator size

    LinearAllocator linearAllocator(ptr, 10000);

    void* allocatedPtr = linearAllocator.Allocate(size, align);

    EXPECT_EQ(linearAllocator.UsedMemory(), size);
    EXPECT_EQ(linearAllocator.AllocationCount(), 1);

    std::free(ptr);
}

TEST_P(AllocationSizeFixture, LinearClear)
{
    const auto size = GetParam();
    void* ptr = std::malloc(size);

    LinearAllocator linearAllocator(ptr, size);

    linearAllocator.Clear();

    EXPECT_EQ(linearAllocator.Size(), 0);
    EXPECT_EQ(linearAllocator.UsedMemory(), 0);
    EXPECT_EQ(linearAllocator.AllocationCount(), 0);

    std::free(ptr);
}

TEST_P(AllocationSizeFixture, ProxyConstructor)
{
    std::size_t size = GetParam();
    void* ptr = std::malloc(size);

    LinearAllocator allocator = LinearAllocator(ptr, size);
    ProxyAllocator proxy = ProxyAllocator(allocator);

    EXPECT_EQ(proxy.RootPtr(), ptr);
    EXPECT_EQ(proxy.Size(), size);
    EXPECT_EQ(proxy.AllocationCount(), 0);
}

TEST_P(AllocationSizeAndAlignmentFixture, ProxyAllocate)
{
    std::size_t size = GetParam().first;
    std::size_t alignment = GetParam().second;
    void* ptr = std::malloc(size);

    LinearAllocator allocator = LinearAllocator(ptr, size);
    ProxyAllocator proxy = ProxyAllocator(allocator);

    void* allocatedPtr = proxy.Allocate(size, alignment);

    EXPECT_EQ(proxy.AllocationCount(), 1);
    EXPECT_EQ(allocatedPtr, ptr);
}

TEST_P(AllocationSizeAndAlignmentFixture, ProxyAllocateMultiple)
{
    std::size_t size = GetParam().first;
    std::size_t alignment = GetParam().second;
    void* ptr = std::malloc(size * 2);

    LinearAllocator allocator = LinearAllocator(ptr, size * 2);
    ProxyAllocator proxy = ProxyAllocator(allocator);

    EXPECT_EQ(proxy.AllocationCount(), 0);
    EXPECT_EQ(proxy.Size(), size * 2);

    void* allocatedPtr = proxy.Allocate(size, alignment);
    void* allocatedPtr2 = proxy.Allocate(size, alignment);

    if (size % alignment != 0)
    {
        EXPECT_EQ(proxy.AllocationCount(), 1);
        EXPECT_EQ(allocatedPtr, ptr);
        EXPECT_EQ(allocatedPtr2, nullptr);
        return;
    }

    EXPECT_EQ(proxy.AllocationCount(), 2);
    EXPECT_EQ(allocatedPtr, ptr);
    EXPECT_EQ(allocatedPtr2, reinterpret_cast<void*>(reinterpret_cast<std::size_t>(ptr) + size));
}

TEST_P(AllocationSizeAndAlignmentFixture, ProxyAllocateOverflow)
{
    std::size_t size = GetParam().first;
    std::size_t alignment = GetParam().second;
    void* ptr = std::malloc(size);

    LinearAllocator allocator = LinearAllocator(ptr, size);
    ProxyAllocator proxy = ProxyAllocator(allocator);

    void* allocatedPtr = proxy.Allocate(size + 1, alignment);

    EXPECT_EQ(proxy.AllocationCount(), 0);
    EXPECT_EQ(allocatedPtr, nullptr);
}

TEST_P(AllocationSizeAndAlignmentFixture, ProxyAllocateOverflowMultiple)
{
    std::size_t size = GetParam().first;
    std::size_t alignment = GetParam().second;
    void* ptr = std::malloc(size * 2);

    LinearAllocator allocator = LinearAllocator(ptr, size * 2);
    ProxyAllocator proxy = ProxyAllocator(allocator);

    EXPECT_EQ(proxy.AllocationCount(), 0);
    EXPECT_EQ(proxy.Size(), size * 2);

    void* allocatedPtr = proxy.Allocate(size + 1, alignment);
    void* allocatedPtr2 = proxy.Allocate(size + 1, alignment);

    EXPECT_EQ(proxy.AllocationCount(), 1);
    EXPECT_EQ(allocatedPtr, ptr);
    EXPECT_EQ(allocatedPtr2, nullptr);
}