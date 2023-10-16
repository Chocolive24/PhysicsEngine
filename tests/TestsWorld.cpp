#include "gtest/gtest.h"
#include "World.h"

#include <array>

using namespace PhysicsEngine;

struct IntFixture : public ::testing::TestWithParam<int>{};

struct ArrayOfBody : public ::testing::TestWithParam<std::array<Body, 3>>{};

INSTANTIATE_TEST_SUITE_P(World, IntFixture, testing::Values(
        0, 1, 24, 500, 900, -10
        ));

INSTANTIATE_TEST_SUITE_P(World, ArrayOfBody, testing::Values(
        std::array<Body, 3>{Body(), Body(Vec2F::One(), Vec2F::One(), 1.f),
                            Body(Vec2F(50.f, 32.12f), Vec2F(23.f, 45.f), 50.f)},
        std::array<Body, 3>{Body(Vec2F(23.f, -10.12f), Vec2F(-223.f, -0.f), 2.f),
                            Body(Vec2F(50.f, -9832.12f), Vec2F(2543.f, 45000.f), 50019.f),
                            Body(Vec2F(3.f, 1.12f), Vec2F(2.f, 56.f), 0.f)}
));

TEST(World, DefaultConstructor)
{
    World world;

    EXPECT_EQ(world.BodyCount(), 0);
}

TEST_P(IntFixture, Init)
{
    int bodyCount = GetParam();

    World world;
    world.Init(bodyCount);

    if (bodyCount < 0)
    {
        EXPECT_EQ(world.BodyCount(), 0);
        return;
    }

    EXPECT_EQ(world.BodyCount(), bodyCount);
}

TEST(World, CreateAndDestroyBody)
{
    World world;
    world.Init(5);

    auto bodyRef = world.CreateBody();
    auto& body = world.GetBody(bodyRef);
    body = Body(Vec2F::One(), Vec2F::One(), 10.f);

    EXPECT_EQ(bodyRef.Index, 0);
    EXPECT_EQ(bodyRef.GenerationIdx, 0);
    EXPECT_TRUE(world.GetBody(bodyRef).IsValid());

    world.DestroyBody(bodyRef);

    bodyRef = world.CreateBody();
    auto& newBody = world.GetBody(bodyRef);
    newBody = Body(Vec2F::One(), Vec2F::One(), 2.f);

    EXPECT_EQ(bodyRef.Index, 0);
    EXPECT_EQ(bodyRef.GenerationIdx, 1);
    EXPECT_TRUE(world.GetBody(bodyRef).IsValid());

    auto bodyRef2 = world.CreateBody();
    auto& body2 = world.GetBody(bodyRef2);
    body2 = Body(Vec2F::One(), Vec2F::One(), 50.f);

    EXPECT_EQ(bodyRef2.Index, 1);
    EXPECT_EQ(bodyRef2.GenerationIdx, 0);
    EXPECT_TRUE(world.GetBody(bodyRef2).IsValid());

    world.DestroyBody(bodyRef2);

    Body nullBodyRef;

    EXPECT_THROW(nullBodyRef =  world.GetBody(bodyRef2), std::runtime_error);
}

TEST_P(ArrayOfBody, Update)
{
    auto bodies = GetParam();
    std::array<BodyRef, bodies.size()> bodyRefs{};

    World world;
    world.Init(bodies.size());

    float deltaTime = 0.1f;

    Vec2F acceleration, velocity, position;

    for (std::size_t i = 0; i < bodies.size(); i++)
    {
        BodyRef bodyRef = world.CreateBody();
        Body& body = world.GetBody(bodyRef);
        body = bodies[i];

        bodyRefs[i] = bodyRef;

        body.AddForce(Vec2F(1.0f, 0.0f));
        bodies[i].AddForce(Vec2F(1.0f, 0.0f));
    }

    world.Update(deltaTime);

    for (std::size_t i = 0; i < bodies.size(); i++)
    {
        auto b = bodies[i];

        if (!b.IsValid()) continue;

        auto bRef = bodyRefs[i];

        auto body = world.GetBody(bRef);

        acceleration = b.Forces() / b.Mass();
        velocity = b.Velocity() + acceleration * deltaTime;
        position = b.Position() + velocity * deltaTime;

        EXPECT_FLOAT_EQ(body.Position().X, position.X);
        EXPECT_FLOAT_EQ(body.Position().Y, position.Y);

        EXPECT_FLOAT_EQ(body.Velocity().X, velocity.X);
        EXPECT_FLOAT_EQ(body.Velocity().Y, velocity.Y);

        EXPECT_FLOAT_EQ(body.Forces().X, 0.f);
        EXPECT_FLOAT_EQ(body.Forces().Y, 0.f);
    }
}