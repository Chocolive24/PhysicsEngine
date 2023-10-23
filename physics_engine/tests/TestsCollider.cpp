#include "Collider.h"

#include "gtest/gtest.h"

using namespace Math;
using namespace PhysicsEngine;

struct ColliderAttributesFixture : public ::testing::TestWithParam<std::tuple<ColliderRef,
        int, BodyRef, float, float, bool>>{};

INSTANTIATE_TEST_SUITE_P(Collider, ColliderAttributesFixture, testing::Values(
        std::tuple{ColliderRef{0, 0}, 0, BodyRef{0, 0}, 0.f, 0.f, false},
        std::tuple{ColliderRef{7, 2}, 15, BodyRef{7, 2}, 5.f, 10.f, true}
        ));

TEST_P(ColliderAttributesFixture, Constructor)
{
    auto [colRef, shapeIdx, bodyRef, rest, frict, isTrigger] = GetParam();

    Collider collider(colRef, shapeIdx, bodyRef, rest, frict, isTrigger);

    EXPECT_EQ(collider.GetColliderRef().Index, colRef.Index);
    EXPECT_EQ(collider.GetColliderRef().GenerationIdx, colRef.GenerationIdx);

    EXPECT_EQ(collider.ShapeIdx(), shapeIdx);

    EXPECT_EQ(collider.BodyRef().Index, bodyRef.Index);
    EXPECT_EQ(collider.BodyRef().GenerationIdx, bodyRef.GenerationIdx);

    EXPECT_FLOAT_EQ(collider.Restitution(), rest);
    EXPECT_FLOAT_EQ(collider.Friction(), frict);

    EXPECT_EQ(collider.IsTrigger(), isTrigger);
}