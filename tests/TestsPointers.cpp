#include "UniquePtr.h"
#include "SharedPtr.h"

#include "gtest/gtest.h"

struct FloatFixture : public ::testing::TestWithParam<float>{};

INSTANTIATE_TEST_SUITE_P(UniquePtr, FloatFixture, testing::Values(
        0.f, 1.f, 5.f, 99999.11111f
        ));

TEST_P(FloatFixture, UniquePtrConstructorAndDereference)
{
    auto value = GetParam();

    UniquePtr<float> uniquePtr(new float(value));

    EXPECT_FLOAT_EQ(*uniquePtr, value);
    EXPECT_FLOAT_EQ(*(uniquePtr.Get()), value);
}

TEST_P(FloatFixture, UniquePtrDestructor)
{
    auto param = GetParam();
    auto* floatPtr = new float(param);

    // Expect that the value is the same.
    EXPECT_FLOAT_EQ(*floatPtr, param);

    {
        UniquePtr<float> ptr(floatPtr);
    } // Call the destructor.

    // Expect that the value is undefined.
    EXPECT_NE(*floatPtr, param);
}

TEST_P(FloatFixture, SharedPtrConstructorAndDereference)
{
    auto value = GetParam();

    SharedPtr<float> sharedPtr(new float(value));

    EXPECT_FLOAT_EQ(*sharedPtr, value);
    EXPECT_FLOAT_EQ(*(sharedPtr.Get()), value);

    EXPECT_EQ(sharedPtr.SharedCount(), 1);
}

TEST_P(FloatFixture, SharedPtrCopyConstructor)
{
    auto param = GetParam();
    auto* createdPtr = new float(param);

    SharedPtr<float> ptr(createdPtr);
    SharedPtr<float> ptrCopy(ptr);

    EXPECT_EQ(ptr.Get(), createdPtr);
    EXPECT_EQ(ptrCopy.Get(), createdPtr);
    EXPECT_EQ(*ptr.Get(), param);
    EXPECT_EQ(*ptrCopy.Get(), param);

    EXPECT_EQ(ptr.SharedCount(), 2);
    EXPECT_EQ(ptrCopy.SharedCount(), 2);
}

//TEST(SharedPtrTest, AssignmentOperator) {
//    int* intPtr = new int(42);
//    SharedPtr<int> intSharedPtr(intPtr);
//    SharedPtr<int> intSharedPtr2;
//    intSharedPtr2 = intSharedPtr;  // Assignment operator
//
//    EXPECT_EQ(*intSharedPtr2, 42);  // Check the value via operator*
//    EXPECT_EQ(intSharedPtr2.Get(), intPtr);  // Check that Get() returns the original pointer
//}

//TEST_P(FloatFixture, SharedDestructor)
//{
//    auto param = GetParam();
//    auto* floatPtr = new float(param);
//
//    // Expect that the value is the same.
//    EXPECT_FLOAT_EQ(*floatPtr, param);
//
//    {
//        UniquePtr<float> ptr(floatPtr);
//    } // Call the destructor.
//
//    // Expect that the value is undefined.
//    EXPECT_NE(*floatPtr, param);
//}
