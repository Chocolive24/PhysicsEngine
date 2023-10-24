#include "World.h"

#include "gtest/gtest.h"
#include "../../common/include/Metrics.h"

#include <array>

using namespace PhysicsEngine;
using namespace Math;

struct IntFixture : public ::testing::TestWithParam<int>{};

struct ArrayOfBody : public ::testing::TestWithParam<std::array<Body, 3>>{};

struct PairOfCircle : public ::testing::TestWithParam<std::pair<CircleF , CircleF>>{};

struct PairOfRect: public ::testing::TestWithParam<std::pair<RectangleF, RectangleF>>{};

struct PairOfCircleAndRect : public ::testing::TestWithParam<std::pair<CircleF, RectangleF>>{};

class TestContactListener : public ContactListener
{
public:
    bool Enter = false;
    bool Stay = false;
    bool Exit = false;

    void OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA,
                        PhysicsEngine::ColliderRef colliderRefB) noexcept override
    {
        Enter = true;
        Stay = false;
        Exit = false;
    }

    void OnTriggerStay(PhysicsEngine::ColliderRef colliderRefA,
                        PhysicsEngine::ColliderRef colliderRefB) noexcept override
    {
        Enter = false;
        Stay = true;
        Exit = false;
    }

    void OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA,
                        PhysicsEngine::ColliderRef colliderRefB) noexcept override
    {
        Enter = false;
        Stay = false;
        Exit = true;
    }
};

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

//INSTANTIATE_TEST_SUITE_P(World, PairOfCircle, testing::Values(
//        std::pair{CircleF(Vec2F::Zero(), 0.f), CircleF(Vec2F::Zero(), 0.f)},
//        std::pair{CircleF(Vec2F(10.f, 10.f), 10.f), CircleF(Vec2F(2, 3), 5.f)},
//        std::pair{CircleF(Vec2F(-510.45f, -3210.f), 3.f), CircleF(Vec2F(29.32f, 345.987f), 5.f)}
//        ));
//
//INSTANTIATE_TEST_SUITE_P(World, PairOfRect, testing::Values(
//        std::pair{RectangleF(Vec2F::Zero(), Vec2F::Zero()),
//                  RectangleF(Vec2F::Zero(), Vec2F::Zero())},
//        std::pair{RectangleF(Vec2F(10.f, 10.f), Vec2F(20.f, 20.f)),
//                  RectangleF(Vec2F(15.f, 15.f), Vec2F(17.f, 17.f))},
//        std::pair{RectangleF(Vec2F(1670.f, 1890.f), Vec2F(2210.f, 27890.f)),
//                  RectangleF(Vec2F(15.f, 15.f), Vec2F(17.f, 17.f))}
//        ));
//
//INSTANTIATE_TEST_SUITE_P(World, PairOfCircleAndRect, testing::Values(
//        std::pair{CircleF(Vec2F::Zero(), 0.f),
//                  RectangleF(Vec2F::Zero(), Vec2F::Zero())},
//        std::pair{CircleF(Vec2F(10.f, 10.f), 10.f),
//                  RectangleF(Vec2F(5.f, 5.f), Vec2F(7.f, 7.f))},
//        std::pair{CircleF(Vec2F(1056.f, 1031.f), 1.f),
//                  RectangleF(Vec2F(5.f, 5.f), Vec2F(7.f, 7.f))}
//));

TEST(World, DefaultConstructor)
{
    World world;

    EXPECT_EQ(world.AllocatedBodies(), 0);
}

TEST_P(IntFixture, Init)
{
    int bodyCount = GetParam();

    World world;
    world.Init(bodyCount);

    if (bodyCount < 0)
    {
        EXPECT_EQ(world.AllocatedBodies(), 0);
        return;
    }

    EXPECT_EQ(world.AllocatedBodies(), bodyCount);
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

        body.ApplyForce(Vec2F(1.0f, 0.0f));
        bodies[i].ApplyForce(Vec2F(1.0f, 0.0f));
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

TEST(World, CreateAndDestroyCircleCollider)
{
    World world;
    world.Init(5);

    auto bodyRef = world.CreateBody();
    auto& body = world.GetBody(bodyRef);
    body = Body(Vec2F::One(), Vec2F::One(), 10.f);

    auto colRef = world.CreateCircleCollider(bodyRef);
    auto& collider = world.GetCollider(colRef);

    EXPECT_EQ(colRef.Index, 0);
    EXPECT_EQ(colRef.GenerationIdx, 0);
    EXPECT_TRUE(world.GetCollider(colRef).IsValid());

    EXPECT_TRUE(world.GetCircleCollider(collider.ShapeIdx()).IsValid());

    world.DestroyCollider(colRef);

    bodyRef = world.CreateBody();
    auto& newBody = world.GetBody(bodyRef);
    newBody = Body(Vec2F::One(), Vec2F::One(), 2.f);

    colRef = world.CreateCircleCollider(bodyRef);
    auto& newCollider = world.GetCollider(colRef);

    EXPECT_EQ(colRef.Index, 0);
    EXPECT_EQ(colRef.GenerationIdx, 1);
    EXPECT_TRUE(world.GetCollider(colRef).IsValid());

    EXPECT_TRUE(world.GetCircleCollider(newCollider.ShapeIdx()).IsValid());

    auto bodyRef2 = world.CreateBody();
    auto& body2 = world.GetBody(bodyRef2);
    body2 = Body(Vec2F::One(), Vec2F::One(), 50.f);

    auto colRef2 = world.CreateCircleCollider(bodyRef2);
    auto& collider2 = world.GetCollider(colRef2);

    EXPECT_EQ(colRef2.Index, 1);
    EXPECT_EQ(colRef2.GenerationIdx, 0);
    EXPECT_TRUE(world.GetCollider(colRef2).IsValid());

    EXPECT_TRUE(world.GetCircleCollider(collider2.ShapeIdx()).IsValid());

    world.DestroyCollider(colRef2);

    Collider nullCollider;

    EXPECT_THROW(nullCollider =  world.GetCollider(colRef2), std::runtime_error);
}

TEST(World, CreateAndDestroyRectCollider)
{
    World world;
    world.Init(5);

    auto bodyRef = world.CreateBody();
    auto& body = world.GetBody(bodyRef);
    body = Body(Vec2F::One(), Vec2F::One(), 10.f);

    auto colRef = world.CreateRectangleCollider(bodyRef);
    auto& collider = world.GetCollider(colRef);

    EXPECT_EQ(colRef.Index, 0);
    EXPECT_EQ(colRef.GenerationIdx, 0);
    EXPECT_TRUE(world.GetCollider(colRef).IsValid());

    EXPECT_TRUE(world.GetRectangleCollider(collider.ShapeIdx()).IsValid());

    world.DestroyCollider(colRef);

    bodyRef = world.CreateBody();
    auto& newBody = world.GetBody(bodyRef);
    newBody = Body(Vec2F::One(), Vec2F::One(), 2.f);

    colRef = world.CreateRectangleCollider(bodyRef);
    auto& newCollider = world.GetCollider(colRef);

    EXPECT_EQ(colRef.Index, 0);
    EXPECT_EQ(colRef.GenerationIdx, 1);
    EXPECT_TRUE(world.GetCollider(colRef).IsValid());

    EXPECT_TRUE(world.GetRectangleCollider(newCollider.ShapeIdx()).IsValid());

    auto bodyRef2 = world.CreateBody();
    auto& body2 = world.GetBody(bodyRef2);
    body2 = Body(Vec2F::One(), Vec2F::One(), 50.f);

    auto colRef2 = world.CreateRectangleCollider(bodyRef2);
    auto& collider2 = world.GetCollider(colRef2);

    EXPECT_EQ(colRef2.Index, 1);
    EXPECT_EQ(colRef2.GenerationIdx, 0);
    EXPECT_TRUE(world.GetCollider(colRef2).IsValid());

    EXPECT_TRUE(world.GetRectangleCollider(collider2.ShapeIdx()).IsValid());

    world.DestroyCollider(colRef2);

    Collider nullCollider;

    EXPECT_THROW(nullCollider =  world.GetCollider(colRef2), std::runtime_error);
}

TEST(World, CreateAndDestroyPolygonCollider)
{
    World world;
    world.Init(5);

    auto bodyRef = world.CreateBody();
    auto& body = world.GetBody(bodyRef);
    body = Body(Vec2F::One(), Vec2F::One(), 10.f);

    auto colRef = world.CreatePolygonCollider(bodyRef);
    auto& collider = world.GetCollider(colRef);

    EXPECT_EQ(colRef.Index, 0);
    EXPECT_EQ(colRef.GenerationIdx, 0);
    EXPECT_TRUE(world.GetCollider(colRef).IsValid());

    EXPECT_TRUE(world.GetPolygonCollider(collider.ShapeIdx()).IsValid());

    world.DestroyCollider(colRef);

    bodyRef = world.CreateBody();
    auto& newBody = world.GetBody(bodyRef);
    newBody = Body(Vec2F::One(), Vec2F::One(), 2.f);

    colRef = world.CreatePolygonCollider(bodyRef);
    auto& newCollider = world.GetCollider(colRef);

    EXPECT_EQ(colRef.Index, 0);
    EXPECT_EQ(colRef.GenerationIdx, 1);
    EXPECT_TRUE(world.GetCollider(colRef).IsValid());

    EXPECT_EQ(world.GetPolygonCollider(newCollider.ShapeIdx()).VerticesCount(), 3);

    EXPECT_TRUE(world.GetPolygonCollider(newCollider.ShapeIdx()).IsValid());

    auto bodyRef2 = world.CreateBody();
    auto& body2 = world.GetBody(bodyRef2);
    body2 = Body(Vec2F::One(), Vec2F::One(), 50.f);

    auto colRef2 = world.CreatePolygonCollider(bodyRef2);
    auto& collider2 = world.GetCollider(colRef2);

    EXPECT_EQ(colRef2.Index, 1);
    EXPECT_EQ(colRef2.GenerationIdx, 0);
    EXPECT_TRUE(world.GetCollider(colRef2).IsValid());

    EXPECT_TRUE(world.GetPolygonCollider(collider2.ShapeIdx()).IsValid());

    world.DestroyCollider(colRef2);

    Collider nullCollider;

    EXPECT_THROW(nullCollider =  world.GetCollider(colRef2), std::runtime_error);
}

TEST(World, UpdateCollisionDetectionCircle)
{
    CircleF c1(Vec2F::Zero(), 0.5f);
    CircleF c2(Vec2F(0.03f, 0.03f), 0.2f);

    World world;
    world.Init(2);

    TestContactListener testContactListener;
    world.SetContactListener(&testContactListener);

    float deltaTime = 0.1f;

    auto bodyRef = world.CreateBody();
    auto& body = world.GetBody(bodyRef);
    body = Body(c1.Center(), Vec2F::Zero(), 1);

    auto c1ColRef = world.CreateCircleCollider(bodyRef);
    auto& collider = world.GetCollider(c1ColRef);
    collider.SetIsTrigger(true);
    world.GetCircleCollider(collider.ShapeIdx()).SetRadius(c1.Radius());

    auto bodyRef2 = world.CreateBody();
    auto& body2 = world.GetBody(bodyRef2);
    body2 = Body(c2.Center(), Vec2F::Zero(), 1);

    auto c2ColRef = world.CreateCircleCollider(bodyRef2);
    auto& collider2 = world.GetCollider(c2ColRef);
    collider2.SetIsTrigger(true);
    world.GetCircleCollider(collider2.ShapeIdx()).SetRadius(c2.Radius());

    // First Update, circle collide :
    world.Update(0.1f);

    EXPECT_TRUE(testContactListener.Enter);
    EXPECT_FALSE(testContactListener.Stay);
    EXPECT_FALSE(testContactListener.Exit);

    // Second Update, circle always collide :
    world.Update(0.1f);

    EXPECT_FALSE(testContactListener.Enter);
    EXPECT_TRUE(testContactListener.Stay);
    EXPECT_FALSE(testContactListener.Exit);

    // Third Update, circle stop collide :
    world.GetBody(bodyRef).SetPosition(Math::Vec2F(10.f, 10.f));

    world.Update(0.1f);

    EXPECT_FALSE(testContactListener.Enter);
    EXPECT_FALSE(testContactListener.Stay);
    EXPECT_TRUE(testContactListener.Exit);
}

TEST(World, UpdateCollisionDetectionRect)
{
    RectangleF r1(Vec2F::Zero(), Vec2F(1.f, 1.f));
    RectangleF r2(Vec2F(0.3f, 0.3f), Vec2F(0.7f, 0.7f));

    World world;
    world.Init(2);

    TestContactListener testContactListener;
    world.SetContactListener(&testContactListener);

    float deltaTime = 0.1f;

    auto bodyRef = world.CreateBody();
    auto& body = world.GetBody(bodyRef);
    body = Body(r1.Center(), Vec2F::Zero(), 1);

    auto r1ColRef = world.CreateRectangleCollider(bodyRef);
    auto& collider = world.GetCollider(r1ColRef);
    collider.SetIsTrigger(true);
    world.GetRectangleCollider(collider.ShapeIdx()).SetHalfSize(r1.Size() / 2.f);

    auto bodyRef2 = world.CreateBody();
    auto& body2 = world.GetBody(bodyRef2);
    body2 = Body(r2.Center(), Vec2F::Zero(), 1);

    auto r2ColRef = world.CreateCircleCollider(bodyRef2);
    auto& collider2 = world.GetCollider(r2ColRef);
    collider2.SetIsTrigger(true);
    world.GetRectangleCollider(collider2.ShapeIdx()).SetHalfSize(r2.Size() / 2.f);

    // First Update, circle collide :
    world.Update(0.1f);

    EXPECT_TRUE(testContactListener.Enter);
    EXPECT_FALSE(testContactListener.Stay);
    EXPECT_FALSE(testContactListener.Exit);

    // Second Update, circle always collide :
    world.Update(0.1f);

    EXPECT_FALSE(testContactListener.Enter);
    EXPECT_TRUE(testContactListener.Stay);
    EXPECT_FALSE(testContactListener.Exit);

    // Third Update, circle stop collide :
    world.GetBody(bodyRef).SetPosition(Math::Vec2F(10.f, 10.f));

    world.Update(0.1f);

    EXPECT_FALSE(testContactListener.Enter);
    EXPECT_FALSE(testContactListener.Stay);
    EXPECT_TRUE(testContactListener.Exit);
}

TEST(World, UpdateCollisionDetectionCircleAndRect)
{
    CircleF c1(Vec2F::Zero(), 0.5f);
    RectangleF r2(Vec2F(0.3f, 0.3f), Vec2F(0.7f, 0.7f));

    World world;
    world.Init(2);

    TestContactListener testContactListener;
    world.SetContactListener(&testContactListener);

    float deltaTime = 0.1f;

    auto bodyRef = world.CreateBody();
    auto& body = world.GetBody(bodyRef);
    body = Body(c1.Center(), Vec2F::Zero(), 1);

    auto c1ColRef = world.CreateCircleCollider(bodyRef);
    auto& collider = world.GetCollider(c1ColRef);
    collider.SetIsTrigger(true);
    world.GetCircleCollider(collider.ShapeIdx()).SetRadius(c1.Radius());

    auto bodyRef2 = world.CreateBody();
    auto& body2 = world.GetBody(bodyRef2);
    body2 = Body(r2.Center(), Vec2F::Zero(), 1);

    auto r2ColRef = world.CreateCircleCollider(bodyRef2);
    auto& collider2 = world.GetCollider(r2ColRef);
    collider2.SetIsTrigger(true);
    world.GetRectangleCollider(collider2.ShapeIdx()).SetHalfSize(r2.Size() / 2.f);

    // First Update, circle collide :
    world.Update(0.1f);

    EXPECT_TRUE(testContactListener.Enter);
    EXPECT_FALSE(testContactListener.Stay);
    EXPECT_FALSE(testContactListener.Exit);

    // Second Update, circle always collide :
    world.Update(0.1f);

    EXPECT_FALSE(testContactListener.Enter);
    EXPECT_TRUE(testContactListener.Stay);
    EXPECT_FALSE(testContactListener.Exit);

    // Third Update, circle stop collide :
    world.GetBody(bodyRef).SetPosition(Math::Vec2F(10.f, 10.f));

    world.Update(0.1f);

    EXPECT_FALSE(testContactListener.Enter);
    EXPECT_FALSE(testContactListener.Stay);
    EXPECT_TRUE(testContactListener.Exit);
}

TEST(World, UpdateCollisionDetectionPolygon)
{
    std::vector<Vec2F> v1 = {
            Vec2F::Zero(),
            Vec2F(1.f, 0.f),
            Vec2F(0.5f, 0.3f),
            Vec2F(0.7f, 0.5f),
            Vec2F(0.9f, 0.7f)
    };

    std::vector<Vec2F> v2 = {
            Vec2F(0.1f, 0.1f),
            Vec2F(0.8f, 0.1f),
            Vec2F(0.4f, 0.25f),
            Vec2F(0.6f, 0.6f),
            Vec2F(0.8f, 0.5f)
    };

    PolygonF p1(v1);
    PolygonF p2(v2);

    World world;
    world.Init(2);

    TestContactListener testContactListener;
    world.SetContactListener(&testContactListener);

    float deltaTime = 0.1f;

    auto bodyRef = world.CreateBody();
    auto& body = world.GetBody(bodyRef);
    body = Body(p1.Center(), Vec2F::Zero(), 1);

    auto c1ColRef = world.CreatePolygonCollider(bodyRef);
    auto& collider = world.GetCollider(c1ColRef);
    collider.SetIsTrigger(true);
    world.GetPolygonCollider(collider.ShapeIdx()).SetVertices(p1.Vertices());

    auto bodyRef2 = world.CreateBody();
    auto& body2 = world.GetBody(bodyRef2);
    body2 = Body(p2.Center(), Vec2F::Zero(), 1);

    auto c2ColRef = world.CreatePolygonCollider(bodyRef2);
    auto& collider2 = world.GetCollider(c2ColRef);
    collider2.SetIsTrigger(true);
    world.GetPolygonCollider(collider2.ShapeIdx()).SetVertices(p2.Vertices());

    // First Update, circle collide :
    world.Update(0.1f);

    EXPECT_TRUE(testContactListener.Enter);
    EXPECT_FALSE(testContactListener.Stay);
    EXPECT_FALSE(testContactListener.Exit);

    // Second Update, circle always collide :
    world.Update(0.1f);

    EXPECT_FALSE(testContactListener.Enter);
    EXPECT_TRUE(testContactListener.Stay);
    EXPECT_FALSE(testContactListener.Exit);

    // Third Update, circle stop collide :
    world.GetBody(bodyRef).SetPosition(Math::Vec2F(100.f, 100.f));

    world.Update(0.1f);

    EXPECT_FALSE(testContactListener.Enter);
    EXPECT_FALSE(testContactListener.Stay);
    EXPECT_TRUE(testContactListener.Exit);
}