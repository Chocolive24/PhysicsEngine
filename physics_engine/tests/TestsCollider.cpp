#include "Collider.h"

#include "gtest/gtest.h"

using namespace Math;
using namespace PhysicsEngine;

struct ColliderAttributesFixture : public ::testing::TestWithParam<std::tuple<float, float, bool>>{};

struct ColliderShapeFixture : public ::testing::TestWithParam<ShapeType> {};

struct RefFixture : public ::testing::TestWithParam<std::pair<std::size_t, std::size_t>> {};

struct ShapeIdxFixture : public ::testing::TestWithParam<int> {};

struct FloatFixture : public ::testing::TestWithParam<float> {};

struct PairOfRefFixture : public ::testing::TestWithParam<std::pair<ColliderRef, ColliderRef>> {};

struct PairOfColliderPairFixture : public ::testing::TestWithParam<std::pair<ColliderPair, ColliderPair>> {};

INSTANTIATE_TEST_SUITE_P(Collider, ColliderAttributesFixture, testing::Values(
        std::tuple{0.f, 0.f, false},
        std::tuple{ 5.f, 10.f, true}
        ));

INSTANTIATE_TEST_SUITE_P(Collider, ColliderShapeFixture, testing::Values(
        ShapeType::Circle, ShapeType::Rectangle, ShapeType::Polygon, ShapeType::None
));

INSTANTIATE_TEST_SUITE_P(Collider, RefFixture, testing::Values(
        std::pair{0, 0},
        std::pair{ 5, 10},
        std::pair{ 3, 25}
));

INSTANTIATE_TEST_SUITE_P(Collider, ShapeIdxFixture, testing::Values(
        0, 1, 2, 5, 10, 1000
));

INSTANTIATE_TEST_SUITE_P(Collider, FloatFixture, testing::Values(
        0.f, 1.f, 2.25f, 5.000001f, -10.987654321f, 1000.99999f
));

TEST(Collider, DefaultConstructor)
{
    Collider collider;

    EXPECT_FLOAT_EQ(collider.Restitution(), -1.f);
    EXPECT_FLOAT_EQ(collider.Friction(), -1.f);

    EXPECT_FALSE(collider.IsTrigger());
}

INSTANTIATE_TEST_SUITE_P(Collider, PairOfRefFixture, testing::Values(
        std::pair{ ColliderRef{0, 0}, ColliderRef{0, 0}},
        std::pair{ ColliderRef{1, 5}, ColliderRef{2, 3}},
        std::pair{ ColliderRef{1, 1}, ColliderRef{1, 1}},
        std::pair{ ColliderRef{50, 34}, ColliderRef{98, 100}}
));

INSTANTIATE_TEST_SUITE_P(Collider, PairOfColliderPairFixture, testing::Values(
        std::pair{ ColliderPair{
            ColliderRef{0, 0},
            ColliderRef{0, 0}},
                   ColliderPair{
            ColliderRef{0, 0},
            ColliderRef{0, 0}}},
        std::pair{ ColliderPair{
                ColliderRef{10, 20},
                ColliderRef{80, 30}},
                   ColliderPair{
                           ColliderRef{9, 4},
                           ColliderRef{5, 1}}}
));

TEST_P(ColliderAttributesFixture, Constructor)
{
    auto [rest, frict, isTrigger] = GetParam();

    Collider collider(rest, frict, isTrigger);

    EXPECT_FLOAT_EQ(collider.Restitution(), rest);
    EXPECT_FLOAT_EQ(collider.Friction(), frict);

    EXPECT_EQ(collider.IsTrigger(), isTrigger);
}

TEST_P(ColliderShapeFixture, GetAndSetShape)
{
    auto shape = GetParam();

    Collider col;
    EXPECT_EQ(col.Shape(), ShapeType::None);

    col.SetShape(shape);
    EXPECT_EQ(col.Shape(), shape);
}

TEST_P(RefFixture, GetAndSetColRef)
{
    auto [idx, genIdx] = GetParam();
    Collider col;

    col.SetColliderRef(ColliderRef{idx, genIdx});

    EXPECT_EQ(col.GetColliderRef().Index, idx);
    EXPECT_EQ(col.GetColliderRef().GenerationIdx, genIdx);
}

TEST_P(ShapeIdxFixture, GetAndSetShapeIdx)
{
    auto shapeIdx = GetParam();

    Collider collider;

    EXPECT_EQ(collider.ShapeIdx(), -1);

    collider.SetShapeIdx(shapeIdx);

    // Check if the SetShapeIdx function correctly sets the shape index.
    EXPECT_EQ(collider.ShapeIdx(), shapeIdx);
}

TEST_P(RefFixture, GetAndSetBodyRef)
{
    auto [idx, genIdx] = GetParam();
    Collider col;

    col.SetBodyRef(BodyRef{idx, genIdx});

    EXPECT_EQ(col.GetBodyRef().Index, idx);
    EXPECT_EQ(col.GetBodyRef().GenerationIdx, genIdx);
}

TEST_P(FloatFixture, Restitution)
{
    auto rest = GetParam();

    Collider collider;
    EXPECT_FLOAT_EQ(collider.Restitution(), -1.f);

    collider.SetRestitution(rest);

    EXPECT_FLOAT_EQ(collider.Restitution(), rest);
}

TEST_P(FloatFixture, Friction)
{
    auto frict = GetParam();

    Collider collider;
    EXPECT_FLOAT_EQ(collider.Friction(), -1.f);

    collider.SetRestitution(frict);

    EXPECT_FLOAT_EQ(collider.Restitution(), frict);
}

TEST(Collider, IsTrigger)
{
    Collider collider;

    EXPECT_FALSE(collider.IsTrigger());

    collider.SetIsTrigger(true);

    EXPECT_TRUE(collider.IsTrigger());
}

TEST_P(ColliderShapeFixture, IsValid)
{
    auto shape = GetParam();

    Collider collider;
    collider.SetShape(shape);

    EXPECT_EQ(collider.IsValid(), shape != ShapeType::None);
}

TEST(ColliderPair, ColliderPairDefaultConstructor)
{
    ColliderPair colliderPair{};

    EXPECT_EQ(colliderPair.ColliderA, ColliderRef());
    EXPECT_EQ(colliderPair.ColliderB, ColliderRef());
}

TEST_P(PairOfRefFixture, ColliderPairConstructor)
{
    auto [colliderRef1, colliderRef2] = GetParam();

    ColliderPair colliderPair{ colliderRef1, colliderRef2 };

    EXPECT_EQ(colliderPair.ColliderA, colliderRef1);
    EXPECT_EQ(colliderPair.ColliderB, colliderRef2);
}

TEST_P(PairOfColliderPairFixture, IsEqualOperator)
{
    auto [colPair1, colPair2] = GetParam();

    EXPECT_EQ(colPair1 == colPair2,
              colPair1.ColliderA == colPair2.ColliderA && colPair1.ColliderB == colPair2.ColliderB
              || colPair1.ColliderA == colPair2.ColliderB && colPair1.ColliderB == colPair2.ColliderA);
}