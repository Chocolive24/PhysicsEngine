#include "gtest/gtest.h"
#include "../include/Body.h"

struct PairOfVec2FFixture : public ::testing::TestWithParam<std::pair<Vec2F, Vec2F>>{};

INSTANTIATE_TEST_SUITE_P(Body, PairOfVec2FFixture, testing::Values(
        std::pair{Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)},
        std::pair{Vec2F(1000.24567f, -0.0000001), Vec2F(-56.3333f, 123.321f)}
        ));

TEST_P(PairOfVec2FFixture, Constructor)
{
    auto [pos, vel] = GetParam();

    Body b(pos, vel);

    EXPECT_FLOAT_EQ(b.Position.X, pos.X);
    EXPECT_FLOAT_EQ(b.Position.Y, pos.Y);

    EXPECT_FLOAT_EQ(b.Velocity.X, vel.X);
    EXPECT_FLOAT_EQ(b.Velocity.Y, vel.Y);
}