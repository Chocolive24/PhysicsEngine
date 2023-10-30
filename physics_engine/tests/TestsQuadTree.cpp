#include "QuadTree.h"
#include "World.h"

#include "gtest/gtest.h"
#include "Random.h"

using namespace PhysicsEngine;
using namespace Math;

struct BoundaryFixture : public ::testing::TestWithParam<RectangleF> {};

struct ColliderNumberFixture : public ::testing::TestWithParam<int> {};

INSTANTIATE_TEST_SUITE_P(QuadNode, BoundaryFixture, testing::Values(
        RectangleF(Vec2F::Zero(), Vec2F::Zero()),
        RectangleF(Vec2F::One(), Vec2F::One()),
        RectangleF(Vec2F(150.234f, 8764.12232f), Vec2F(-9054.233, -0.11111f)),
        RectangleF(Vec2F(-1, 678.31f), Vec2F(10.34f, -27.54f))
        ));

INSTANTIATE_TEST_SUITE_P(QuadTree, ColliderNumberFixture, testing::Values(0, 1, 10, 100, 100, 321, 14, 5789));

TEST(QuadNode, DefaultConstructor)
{
    QuadNode node;

    EXPECT_EQ(node.Boundary.MinBound(), Vec2F::Zero());
    EXPECT_EQ(node.Boundary.MaxBound(), Vec2F::Zero());

    for (const auto& child : node.Children)
    {
        EXPECT_EQ(child, nullptr);
    }

    EXPECT_EQ(node.Colliders.size(), 0);
}

TEST_P(BoundaryFixture, ConstructorWithBoundary)
{
    auto boundary = GetParam();

    QuadNode node(boundary);

    EXPECT_EQ(node.Boundary.MinBound(), boundary.MinBound());
    EXPECT_EQ(node.Boundary.MaxBound(), boundary.MaxBound());
}

TEST(QuadTree, DefaultConstructor)
{
    QuadTree quadTree;

    EXPECT_EQ(quadTree.PossiblePairs().size(), 0);
}

void InitRecursive(const QuadNode& node)
{
    EXPECT_EQ(node.Colliders.capacity(), QuadNode::MaxColliderNbr);

    if (node.Children[0] != nullptr)
    {
        for (const auto& child : node.Children)
        {
            InitRecursive(*child);
        }
    }
}

TEST(QuadTree, Init)
{
    QuadTree quadTree;
    quadTree.Init();

    InitRecursive(quadTree.RootNode());
}

void CheckRecursive(const QuadNode& node, const QuadNode& expectedNode)
{
    for (std::size_t i = 0; i < node.Colliders.size(); i++)
    {
        EXPECT_EQ(node.Colliders[i].Rectangle.MinBound(), expectedNode.Colliders[i].Rectangle.MinBound());
        EXPECT_EQ(node.Colliders[i].Rectangle.MaxBound(), expectedNode.Colliders[i].Rectangle.MaxBound());
        EXPECT_EQ(node.Colliders[i].ColRef, expectedNode.Colliders[i].ColRef);
    }

    if (node.Children[0] != nullptr)
    {
        for (std::size_t i = 0; i < node.Children.size(); i++)
        {
            CheckRecursive(*node.Children[i], *expectedNode.Children[i]);
        }
    }
}

void insertRecursive(QuadNode& node,
                     Math::RectangleF simplifiedShape,
                     ColliderRef colliderRef,
                     int depth,
                     int maxDepth) noexcept
{
    // If the node doesn't have any children.
    if (node.Children[0] == nullptr)
    {
        // Add the simplified collider to the node.
        SimplifiedCollider simplifiedCollider = {colliderRef, simplifiedShape};
        node.Colliders.push_back(simplifiedCollider);

        // If the node has fewer colliders than the max number and the depth is not equal to the max depth.
        if (node.Colliders.size() > QuadNode::MaxColliderNbr && depth != maxDepth)
        {
            // Subdivide the node rectangle in 4 rectangle.
            const auto center = node.Boundary.Center();
            const auto halfSize = node.Boundary.HalfSize();

            const auto topMiddle = Math::Vec2F(center.X, center.Y + halfSize.Y);
            const auto topRightCorner = center + halfSize;
            const auto rightMiddle = Math::Vec2F(center.X + halfSize.X, center.Y);
            const auto bottomMiddle = Math::Vec2F(center.X, center.Y - halfSize.Y);
            const auto bottomLeftCorner = center - halfSize;
            const auto leftMiddle = Math::Vec2F(center.X - halfSize.X, center.Y);

            node.Children[0] = new QuadNode(Math::RectangleF(leftMiddle, topMiddle));
            node.Children[1] = new QuadNode(Math::RectangleF(center, topRightCorner));
            node.Children[2] = new QuadNode(Math::RectangleF(bottomLeftCorner, center));
            node.Children[3] = new QuadNode(Math::RectangleF(bottomMiddle, rightMiddle));

            std::vector<SimplifiedCollider> remainingColliders;

            for (const auto &col: node.Colliders)
            {
                int boundInterestCount = 0;
                QuadNode *intersectNode = nullptr;

                for (const auto &child: node.Children)
                {
                    if (Math::Intersect(child->Boundary, col.Rectangle))
                    {
                        boundInterestCount++;
                        intersectNode = child;
                    }
                }

                if (boundInterestCount == 1)
                {
                    insertRecursive(*intersectNode,
                                    col.Rectangle,
                                    col.ColRef,
                                    depth + 1,
                                    maxDepth);
                }
                else
                {
                    remainingColliders.push_back(col);
                }
            }

            node.Colliders = std::move(remainingColliders);
        }
    }

    // If the node has children.
    else
    {
        int boundInterestCount = 0;
        QuadNode* intersectNode = nullptr;

        for (const auto& child : node.Children)
        {
            if (Math::Intersect(child->Boundary, simplifiedShape))
            {
                boundInterestCount++;
                intersectNode = child;
            }
        }

        if (boundInterestCount == 1)
        {
            depth++;
            insertRecursive(*intersectNode,
                            simplifiedShape,
                            colliderRef,
                            depth,
                            maxDepth);
        }
        else
        {
            SimplifiedCollider simplifiedCollider = {colliderRef, simplifiedShape};
            node.Colliders.push_back(simplifiedCollider);
        }
    }
}

TEST_P(ColliderNumberFixture, Insert)
{
    World world;
    world.Init();

    QuadTree quadTree;
    quadTree.Init();

    const auto colNbr = GetParam();

    std::vector<Collider> colliders;
    colliders.reserve(colNbr);

    std::vector<QuadNode> expectedNodes;
    expectedNodes.resize(Math::Pow(QuadNode::BoundaryDivisionCount, quadTree.MaxDepth()),
                         QuadNode());

    for (std::size_t i = 0; i < colNbr; i++)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(1.f, 7.f),
                                 Math::Random::Range(-1.f, -5.f));

        Math::Vec2F rndVelocity(Math::Random::Range(-2.f, 2.f),
                                Math::Random::Range(-2.f, 2.f));

        // Body.
        BodyRef bodyRef = world.CreateBody();
        auto& body = world.GetBody(bodyRef);
        body = PhysicsEngine::Body(rndScreenPos, rndVelocity, 1.f);

        // Collider.
        ColliderRef colRef = world.CreateCollider(bodyRef);
        auto& collider = world.GetCollider(colRef);
        collider.SetIsTrigger(true);
        collider.SetShape(Math::CircleF(Math::Vec2F::Zero(),
                                        Math::Random::Range(0.1f, 0.15f)));

        colliders.push_back(collider);
    }

    for (std::size_t i = 0; i < colliders.size(); i++)
    {
        ColliderRef colliderRef = {i, 0};
        const auto& col = world.GetCollider(colliderRef);

        const auto colShape = col.Shape();

        const auto circle = std::get<Math::CircleF>(colShape);
        const auto radius = circle.Radius();
        const auto simplifiedCircle = Math::RectangleF::FromCenter(
                world.GetBody(col.GetBodyRef()).Position(),
                Math::Vec2F(radius, radius));

        quadTree.Insert(simplifiedCircle, colliderRef);

        insertRecursive(expectedNodes[0],
                        simplifiedCircle,
                        colliderRef,
                        0,
                        quadTree.MaxDepth());
    }

    CheckRecursive(quadTree.RootNode(), expectedNodes[0]);
}

//TEST_P(ColliderNumberFixture, CalculatePossiblePairs)
//{
//    auto colNbr = GetParam();
//
//    std::vector<ColliderPair> expectedPairs;
//    expectedPairs.reserve(colNbr);
//
//    for (std::size_t i = 0; i < colNbr; i++)
//    {
//
//    }
//}