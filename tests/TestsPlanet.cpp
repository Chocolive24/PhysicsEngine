#include "../samples/include/Planet.h"

#include "gtest/gtest.h"

using namespace PhysicsEngine;

struct TupleOfBodyAndTwoFloatFixture : public ::testing::TestWithParam<std::tuple<Body, float, float>>{};

INSTANTIATE_TEST_SUITE_P(Body, TupleOfBodyAndTwoFloatFixture, testing::Values(
        std::tuple{Body(Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)), 0.f, 0.000f},
        std::tuple{Body(Vec2F(-0.0001f, 81.5678f), Vec2F(9876.34f, -65.4321f)),
                   -110.875f, -0.0000005f}
));

TEST_P(TupleOfBodyAndTwoFloatFixture, Constructor)
{
    auto [body, radius, speed] = GetParam();

    Planet p(body, radius);

    EXPECT_FLOAT_EQ(p.GetBody()._position.X, body._position.X);
    EXPECT_FLOAT_EQ(p.GetBody()._position.Y, body._position.Y);
    EXPECT_FLOAT_EQ(p.GetRadius(), radius);
}