/**
 * @headerfile Test the Shape.h classes and functions
 * @author Alexis & cie
 */

#include "Shape.h"

#include "gtest/gtest.h"

using namespace Math;

struct CircleFloatTestFixture : public ::testing::TestWithParam<std::pair<Vec2F, float>> {};
struct CircleIntegerTestFixture : public ::testing::TestWithParam<std::pair<Vec2I, int>> {};

struct CircleFloatTestFixtureWithVec2F : public ::testing::TestWithParam<std::pair<CircleF, Vec2F>> {};
struct CircleIntegerTestFixtureWithVec2I : public ::testing::TestWithParam<std::pair<CircleI, Vec2I>> {};

struct CircleFloatIntersectionTestFixture : public ::testing::TestWithParam<std::pair<CircleF, CircleF>> {};
struct CircleIntegerIntersectionTestFixture : public ::testing::TestWithParam<std::pair<CircleI, CircleI>> {};

struct RectangleFloatTestFixture : public ::testing::TestWithParam<std::pair<Vec2F, Vec2F>> {};
struct RectangleIntegerTestFixture : public ::testing::TestWithParam<std::pair<Vec2I, Vec2I>> {};

struct RectangleFloatTestFixtureWithVec2F : public ::testing::TestWithParam<std::pair<RectangleF, Vec2F>> {};
struct RectangleIntegerTestFixtureWithVec2I : public ::testing::TestWithParam<std::pair<RectangleI, Vec2I>> {};

struct RectangleFloatIntersectionTestFixture : public ::testing::TestWithParam<std::pair<RectangleF, RectangleF>> {};
struct RectangleIntegerIntersectionTestFixture : public ::testing::TestWithParam<std::pair<RectangleI, RectangleI>> {};

struct RectangleCircleFloatIntersectionTestFixture : public ::testing::TestWithParam<std::pair<RectangleF, CircleF>> {};
struct RectangleCircleIntegerIntersectionTestFixture : public ::testing::TestWithParam<std::pair<RectangleI, CircleI>> {};

#pragma region InstantiateParametrizedTests

INSTANTIATE_TEST_SUITE_P(CircleFloat, CircleFloatTestFixture, testing::Values(
    std::make_pair(Vec2F(0.f, 0.f), 0.f),
    std::make_pair(Vec2F(0.f, 0.f), 1.f),
    std::make_pair(Vec2F(1.f, 5.f), 10.f),
    std::make_pair(Vec2F(-1.f, -5.f), 10.f),
    std::make_pair(Vec2F(-1.f, -5.f), -10.f),
    std::make_pair(Vec2F(1.234f, 5.678f), 10.123f),
    std::make_pair(Vec2F(-1.234f, -5.678f), 10.123f)
));

INSTANTIATE_TEST_SUITE_P(CircleInteger, CircleIntegerTestFixture, testing::Values(
    std::make_pair(Vec2I(0, 0), 0),
    std::make_pair(Vec2I(0, 0), 1),
    std::make_pair(Vec2I(1, 5), 10),
    std::make_pair(Vec2I(-1, -5), 10),
    std::make_pair(Vec2I(-1, -5), -10)
));

INSTANTIATE_TEST_SUITE_P(CircleFloat, CircleFloatTestFixtureWithVec2F, testing::Values(
    std::make_pair(CircleF(Vec2F(0.f, 0.f), 0.f), Vec2F(9.f, 18.f)),
    std::make_pair(CircleF(Vec2F(0.f, 0.f), 1.f), Vec2F(0.f, 0.f)),
    std::make_pair(CircleF(Vec2F(1.f, 5.f), 10.f), Vec2F(1.f, 5.9f)),
    std::make_pair(CircleF(Vec2F(-1.f, -5.f), 10.f), Vec2F(-1.f, -4.9f)),
    std::make_pair(CircleF(Vec2F(-1.f, -5.f), -10.f), Vec2F(-1.f, -4.9f)),
    std::make_pair(CircleF(Vec2F(1.234f, 5.678f), 10.123f), Vec2F(1.534f, 5.178f))
));

INSTANTIATE_TEST_SUITE_P(CircleInteger, CircleIntegerTestFixtureWithVec2I, testing::Values(
    std::make_pair(CircleI(Vec2I(0, 0), 0), Vec2I(9, 18)),
    std::make_pair(CircleI(Vec2I(0, 0), 1), Vec2I(0, 0)),
    std::make_pair(CircleI(Vec2I(1, 5), 10), Vec2I(1, 5)),
    std::make_pair(CircleI(Vec2I(-1, -5), 10), Vec2I(-1, -5)),
    std::make_pair(CircleI(Vec2I(-1, -5), -10), Vec2I(-1, -5))
));

INSTANTIATE_TEST_SUITE_P(CircleFloat, CircleFloatIntersectionTestFixture, testing::Values(
    std::make_pair(CircleF(Vec2F(0.f, 0.f), 0.f), CircleF(Vec2F(0.f, 0.f), 0.f)),
    std::make_pair(CircleF(Vec2F(1.f, 1.f), 1.f), CircleF(Vec2F(1.f, 1.f), 1.f)),
    std::make_pair(CircleF(Vec2F(0.f, 0.f), 1.f), CircleF(Vec2F(5.f, 6.f), 1.f)),
    std::make_pair(CircleF(Vec2F(1.f, 5.f), 10.f), CircleF(Vec2F(7.f, 5.f), 10.f)),
    std::make_pair(CircleF(Vec2F(-1.f, -5.f), 10.f), CircleF(Vec2F(-1.f, -8.f), 10.f)),
    std::make_pair(CircleF(Vec2F(-1.f, -5.f), -10.f), CircleF(Vec2F(-1.f, -5.f), -10.f))
));

INSTANTIATE_TEST_SUITE_P(CircleInteger, CircleIntegerIntersectionTestFixture, testing::Values(
    std::make_pair(CircleI(Vec2I(0, 0), 0), CircleI(Vec2I(0, 0), 0)),
    std::make_pair(CircleI(Vec2I(1, 1), 1), CircleI(Vec2I(1, 1), 1)),
    std::make_pair(CircleI(Vec2I(0, 0), 1), CircleI(Vec2I(5, 6), 1)),
    std::make_pair(CircleI(Vec2I(1, 5), 10), CircleI(Vec2I(7, 5), 10)),
    std::make_pair(CircleI(Vec2I(-1, -5), 10), CircleI(Vec2I(-1, -8), 10)),
    std::make_pair(CircleI(Vec2I(-1, -5), -10), CircleI(Vec2I(-1, -8), -10))
));

INSTANTIATE_TEST_SUITE_P(RectangleFloat, RectangleFloatTestFixture, testing::Values(
    std::make_pair(Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)),
    std::make_pair(Vec2F(0.f, 0.f), Vec2F(1.f, 1.f)),
    std::make_pair(Vec2F(1.f, 5.f), Vec2F(10.f, 10.f)),
    std::make_pair(Vec2F(-1.f, -5.f), Vec2F(10.f, 10.f)),
    std::make_pair(Vec2F(-1.f, -5.f), Vec2F(-10.f, -10.f)),
    std::make_pair(Vec2F(1.234f, 5.678f), Vec2F(10.123f, 10.123f)),
    std::make_pair(Vec2F(-1.234f, -5.678f), Vec2F(10.123f, 10.123f))
));

INSTANTIATE_TEST_SUITE_P(RectangleInteger, RectangleIntegerTestFixture, testing::Values(
    std::make_pair(Vec2I(0, 0), Vec2I(0, 0)),
    std::make_pair(Vec2I(0, 0), Vec2I(1, 1)),
    std::make_pair(Vec2I(1, 5), Vec2I(10, 10)),
    std::make_pair(Vec2I(-1, -5), Vec2I(10, 10)),
    std::make_pair(Vec2I(-1, -5), Vec2I(-10, -10))
));

INSTANTIATE_TEST_SUITE_P(RectangleFloat, RectangleFloatTestFixtureWithVec2F, testing::Values(
    std::make_pair(RectangleF(Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)), Vec2F(9.f, 18.f)),
    std::make_pair(RectangleF(Vec2F(0.f, 0.f), Vec2F(1.f, 1.f)), Vec2F(0.f, 0.f)),
    std::make_pair(RectangleF(Vec2F(1.f, 5.f), Vec2F(10.f, 10.f)), Vec2F(1.f, 5.9f)),
    std::make_pair(RectangleF(Vec2F(-1.f, -5.f), Vec2F(10.f, 10.f)), Vec2F(-1.f, -4.9f)),
    std::make_pair(RectangleF(Vec2F(-1.f, -5.f), Vec2F(-10.f, -10.f)), Vec2F(-1.f, -4.9f)),
    std::make_pair(RectangleF(Vec2F(1.234f, 5.678f), Vec2F(10.123f, 10.123f)), Vec2F(1.534f, 5.178f))
));

INSTANTIATE_TEST_SUITE_P(RectangleInteger, RectangleIntegerTestFixtureWithVec2I, testing::Values(
    std::make_pair(RectangleI(Vec2I(0, 0), Vec2I(0, 0)), Vec2I(9, 18)),
    std::make_pair(RectangleI(Vec2I(0, 0), Vec2I(1, 1)), Vec2I(0, 0)),
    std::make_pair(RectangleI(Vec2I(1, 5), Vec2I(10, 10)), Vec2I(1, 5)),
    std::make_pair(RectangleI(Vec2I(-1, -5), Vec2I(10, 10)), Vec2I(-1, -5)),
    std::make_pair(RectangleI(Vec2I(-1, -5), Vec2I(-10, -10)), Vec2I(-1, -5))
));

INSTANTIATE_TEST_SUITE_P(RectangleFloat, RectangleFloatIntersectionTestFixture, testing::Values(
    std::make_pair(RectangleF(Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)), RectangleF(Vec2F(0.f, 0.f), Vec2F(0.f, 0.f))),
    std::make_pair(RectangleF(Vec2F(0.f, 0.f), Vec2F(1.f, 1.f)), RectangleF(Vec2F(0.f, 0.f), Vec2F(1.f, 1.f))),
    std::make_pair(RectangleF(Vec2F(1.f, 5.f), Vec2F(10.f, 10.f)), RectangleF(Vec2F(1.f, 5.f), Vec2F(10.f, 10.f))),
    std::make_pair(RectangleF(Vec2F(-1.f, -5.f), Vec2F(10.f, 10.f)), RectangleF(Vec2F(-1.f, -5.f), Vec2F(10.f, 10.f))),
    std::make_pair(RectangleF(Vec2F(-1.f, -5.f), Vec2F(-10.f, -10.f)), RectangleF(Vec2F(-1.f, -5.f), Vec2F(-10.f, -10.f))),
    std::make_pair(RectangleF(Vec2F(0.f, 0.f), Vec2F(10.f, 10.f)), RectangleF(Vec2F(3.f, -3.f), Vec2F(7.f, 15.f)))
));

INSTANTIATE_TEST_SUITE_P(RectangleInteger, RectangleIntegerIntersectionTestFixture, testing::Values(
    std::make_pair(RectangleI(Vec2I(0, 0), Vec2I(0, 0)), RectangleI(Vec2I(0, 0), Vec2I(0, 0))),
    std::make_pair(RectangleI(Vec2I(0, 0), Vec2I(1, 1)), RectangleI(Vec2I(0, 0), Vec2I(1, 1))),
    std::make_pair(RectangleI(Vec2I(1, 5), Vec2I(10, 10)), RectangleI(Vec2I(1, 5), Vec2I(10, 10))),
    std::make_pair(RectangleI(Vec2I(-1, -5), Vec2I(10, 10)), RectangleI(Vec2I(-1, -5), Vec2I(10, 10))),
    std::make_pair(RectangleI(Vec2I(-1, -5), Vec2I(-10, -10)), RectangleI(Vec2I(-1, -5), Vec2I(-10, -10))),
    std::make_pair(RectangleI(Vec2I(0, 0), Vec2I(10, 10)), RectangleI(Vec2I(3, -3), Vec2I(7, 15)))
));

INSTANTIATE_TEST_SUITE_P(RectangleCircleFloat, RectangleCircleFloatIntersectionTestFixture, testing::Values(
    std::make_pair(RectangleF(Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)), CircleF(Vec2F(0.f, 0.f), 0.f)),
    std::make_pair(RectangleF(Vec2F(0.f, 0.f), Vec2F(1.f, 1.f)), CircleF(Vec2F(0.f, 0.f), 1.f)),
    std::make_pair(RectangleF(Vec2F(1.f, 5.f), Vec2F(10.f, 10.f)), CircleF(Vec2F(1.f, 5.f), 10.f)),
    std::make_pair(RectangleF(Vec2F(-1.f, -5.f), Vec2F(10.f, 10.f)), CircleF(Vec2F(-1.f, -5.f), 10.f)),
    std::make_pair(RectangleF(Vec2F(-1.f, -5.f), Vec2F(-10.f, -10.f)), CircleF(Vec2F(-1.f, -5.f), 10.f)),
    std::make_pair(RectangleF(Vec2F(0.f, 0.f), Vec2F(10.f, 10.f)), CircleF(Vec2F(3.f, -3.f), 7.f))
));

INSTANTIATE_TEST_SUITE_P(RectangleCircleInteger, RectangleCircleIntegerIntersectionTestFixture, testing::Values(
    std::make_pair(RectangleI(Vec2I(0, 0), Vec2I(0, 0)), CircleI(Vec2I(0, 0), 0)),
    std::make_pair(RectangleI(Vec2I(0, 0), Vec2I(1, 1)), CircleI(Vec2I(0, 0), 1)),
    std::make_pair(RectangleI(Vec2I(1, 5), Vec2I(10, 10)), CircleI(Vec2I(1, 5), 10)),
    std::make_pair(RectangleI(Vec2I(-1, -5), Vec2I(10, 10)), CircleI(Vec2I(-1, -5), 10)),
    std::make_pair(RectangleI(Vec2I(-1, -5), Vec2I(-10, -10)), CircleI(Vec2I(-1, -5), 10)),
    std::make_pair(RectangleI(Vec2I(0, 0), Vec2I(10, 10)), CircleI(Vec2I(3, -3), 7))
));

#pragma endregion

#pragma region CircleFloat

TEST_P(CircleFloatTestFixture, CircleFloatConstructor)
{
    auto [center, radius] = GetParam();
    CircleF circle(center, radius);

    EXPECT_EQ(circle.Center(), center);
    EXPECT_EQ(circle.Radius(), Abs(radius));
}

TEST_P(CircleFloatTestFixtureWithVec2F, CircleFloatContains)
{
    auto [circle, point] = GetParam();
    bool contains = (circle.Center() - point).SquareLength() <= circle.Radius() * circle.Radius();

    EXPECT_EQ(circle.Contains(point), contains);
}

TEST_P(CircleFloatIntersectionTestFixture, CircleFloatIntersection)
{
    auto [circle1, circle2] = GetParam();
    bool intersect = (circle1.Center() - circle2.Center()).SquareLength() <= (circle1.Radius() + circle2.Radius()) * (circle1.Radius() + circle2.Radius());

    EXPECT_EQ(Intersect(circle1, circle2), intersect);
}

#pragma endregion

#pragma region CircleInteger

TEST_P(CircleIntegerTestFixture, CircleIntegerConstructor)
{
    auto [center, radius] = GetParam();
    CircleI circle(center, radius);

    EXPECT_EQ(circle.Center(), center);
    EXPECT_EQ(circle.Radius(), Abs(radius));
}

TEST_P(CircleIntegerTestFixtureWithVec2I, CircleIntegerContains)
{
    auto [circle, point] = GetParam();
    bool contains = (circle.Center() - point).SquareLength() <= circle.Radius() * circle.Radius();

    EXPECT_EQ(circle.Contains(point), contains);
}

TEST_P(CircleIntegerIntersectionTestFixture, CircleIntegerIntersection)
{
    auto [circle1, circle2] = GetParam();
    bool intersect = (circle1.Center() - circle2.Center()).SquareLength() <= (circle1.Radius() + circle2.Radius()) * (circle1.Radius() + circle2.Radius());

    EXPECT_EQ(Intersect(circle1, circle2), intersect);
}

#pragma endregion

#pragma region RectangleFloat

TEST_P(RectangleFloatTestFixture, RectangleFloatConstructor)
{
    auto [minBound, maxBound] = GetParam();
    RectangleF rectangle(minBound, maxBound);

    EXPECT_EQ(rectangle.MinBound(), minBound);
    EXPECT_EQ(rectangle.MaxBound(), maxBound);

    EXPECT_EQ(rectangle.Center(), (minBound + maxBound) / 2);
    EXPECT_EQ(rectangle.Size(), maxBound - minBound);
}

TEST_P(RectangleFloatTestFixtureWithVec2F, RectangleFloatContains)
{
    auto [rectangle, point] = GetParam();
    bool contains = rectangle.MinBound().X <= point.X && point.X <=
            rectangle.MaxBound().X && rectangle.MinBound().Y <= point.Y && point.Y <= rectangle.MaxBound().Y;

    EXPECT_EQ(rectangle.Contains(point), contains);
}

TEST_P(RectangleFloatIntersectionTestFixture, RectangleFloatIntersection)
{
    auto [rectangle1, rectangle2] = GetParam();
    bool intersect = rectangle1.MinBound().X <= rectangle2.MaxBound().X && rectangle2.MinBound().X <=
            rectangle1.MaxBound().X && rectangle1.MinBound().Y <= rectangle2.MaxBound().Y && rectangle2.MinBound().Y <= rectangle1.MaxBound().Y;

    EXPECT_EQ(Intersect(rectangle1, rectangle2), intersect);
}

TEST_P(RectangleCircleFloatIntersectionTestFixture, RectangleCircleFloatIntersection)
{
    auto [rectangle, circle] = GetParam();
    bool intersect = false;
    const auto center = circle.Center();

    if (rectangle.Contains(center)) intersect = true;

    const auto minBound = rectangle.MinBound();
    const auto maxBound = rectangle.MaxBound();
    const auto radius = circle.Radius();

    const auto minBoundRect1 = minBound - Vec2F(radius, 0);
    const auto minBoundRect2 = minBound - Vec2F(0, radius);
    const auto maxBoundRect1 = maxBound + Vec2F(radius, 0);
    const auto maxBoundRect2 = maxBound + Vec2F(0, radius);

    // Added circle radius to rectangle bounds
    const RectangleF rectangle1(minBoundRect1, maxBoundRect1);
    const RectangleF rectangle2(minBoundRect2, maxBoundRect2);

    // Check rectangle bounds
    if (rectangle1.Contains(center)) intersect = true;
    if (rectangle2.Contains(center)) intersect = true;

    // Check circles at rectangle corners
    const auto corners = {
        minBound,
        maxBound,
        Vec2F(minBound.X, maxBound.Y),
        Vec2F(maxBound.X, minBound.Y)
    };

    for (const auto& corner : corners)
    {
        if (circle.Contains(corner)) intersect = true;
    }

    EXPECT_EQ(Intersect(rectangle, circle), intersect);
    EXPECT_EQ(Intersect(circle, rectangle), intersect);
}

#pragma endregion

#pragma region RectangleInteger

TEST_P(RectangleIntegerTestFixture, RectangleIntegerConstructor)
{
    auto [minBound, maxBound] = GetParam();
    RectangleI rectangle(minBound, maxBound);

    EXPECT_EQ(rectangle.MinBound(), minBound);
    EXPECT_EQ(rectangle.MaxBound(), maxBound);

    EXPECT_EQ(rectangle.Center(), (minBound + maxBound) / 2);
    EXPECT_EQ(rectangle.Size(), maxBound - minBound);
}

TEST_P(RectangleIntegerTestFixtureWithVec2I, RectangleIntegerContains)
{
    auto [rectangle, point] = GetParam();
    bool contains = rectangle.MinBound().X <= point.X && point.X <=
            rectangle.MaxBound().X && rectangle.MinBound().Y <= point.Y && point.Y <= rectangle.MaxBound().Y;

    EXPECT_EQ(rectangle.Contains(point), contains);
}

TEST_P(RectangleIntegerIntersectionTestFixture, RectangleIntegerIntersection)
{
    auto [rectangle1, rectangle2] = GetParam();
    bool intersect = rectangle1.MinBound().X <= rectangle2.MaxBound().X && rectangle2.MinBound().X <=
            rectangle1.MaxBound().X && rectangle1.MinBound().Y <= rectangle2.MaxBound().Y && rectangle2.MinBound().Y <= rectangle1.MaxBound().Y;

    EXPECT_EQ(Intersect(rectangle1, rectangle2), intersect);
}

TEST_P(RectangleCircleIntegerIntersectionTestFixture, RectangleCircleIntegerIntersection)
{
    auto [rectangle, circle] = GetParam();
    bool intersect = false;
    const auto center = circle.Center();

    if (rectangle.Contains(center)) intersect = true;

    const auto minBound = rectangle.MinBound();
    const auto maxBound = rectangle.MaxBound();
    const auto radius = circle.Radius();

    const auto minBoundRect1 = minBound - Vec2I(radius, 0);
    const auto minBoundRect2 = minBound - Vec2I(0, radius);
    const auto maxBoundRect1 = maxBound + Vec2I(radius, 0);
    const auto maxBoundRect2 = maxBound + Vec2I(0, radius);

    // Added circle radius to rectangle bounds
    const RectangleI rectangle1(minBoundRect1, maxBoundRect1);
    const RectangleI rectangle2(minBoundRect2, maxBoundRect2);

    // Check rectangle bounds
    if (rectangle1.Contains(center)) intersect = true;
    if (rectangle2.Contains(center)) intersect = true;

    // Check circles at rectangle corners
    const auto corners = {
        minBound,
        maxBound,
        Vec2I(minBound.X, maxBound.Y),
        Vec2I(maxBound.X, minBound.Y)
    };

    for (const auto& corner : corners)
    {
        if (circle.Contains(corner)) intersect = true;
    }

    EXPECT_EQ(Intersect(rectangle, circle), intersect);
    EXPECT_EQ(Intersect(circle, rectangle), intersect);
}

#pragma endregion

TEST(PolygonIntersect, PolygonIntersect)
{
    PolygonF polygon(std::vector<Vec2F>{
        Vec2F(0.f, 0.f),
        Vec2F(4.f, 4.f),
        Vec2F(0.f, 4.f)
    });
    PolygonF polygonIntersect(std::vector<Vec2F>{
        Vec2F(1.f, 0.f),
        Vec2F(5.f, 3.f),
        Vec2F(1.f, 5.f)
    });
    PolygonF polygonSpecialIntersect(std::vector<Vec2F>{
            Vec2F(1.f, 0.f),
            Vec2F(5.f, 3.f),
            Vec2F(1.f, 4.f)
    });
    PolygonF polygonSpecialIntersect2(std::vector<Vec2F>{
            Vec2F(1.f, 0.f),
            Vec2F(5.f, 3.f),
            Vec2F(1.f, 3.f)
    });
    PolygonF polygonNotIntersect(std::vector<Vec2F>{
        Vec2F(1.f, 0.f),
        Vec2F(5.f, 0.f),
        Vec2F(5.f, 3.f)
    });

    EXPECT_TRUE(Intersect(polygon, polygonIntersect));
    EXPECT_TRUE(Intersect(polygon, polygonSpecialIntersect));
    EXPECT_TRUE(Intersect(polygon, polygonSpecialIntersect2));
    EXPECT_FALSE(Intersect(polygon, polygonNotIntersect));
}

TEST(PolygonIntersect, PolygonIntersectWithCircle)
{
    PolygonF polygon(std::vector<Vec2F>{
        Vec2F(0.f, 0.f),
        Vec2F(4.f, 4.f),
        Vec2F(0.f, 4.f)
    });
    CircleF circle(Vec2F(1.f, 1.f), 1.f);
    CircleF circleIntersect(Vec2F(1.f, 1.f), 2.f);
    CircleF circleNotIntersect(Vec2F(1.f, 0.f), 0.5f);

    EXPECT_TRUE(Intersect(polygon, circle));
    EXPECT_TRUE(Intersect(polygon, circleIntersect));
    EXPECT_FALSE(Intersect(polygon, circleNotIntersect));
}

TEST(PolygonIntersect, PolygonIntersectWithRectangle)
{
    PolygonF polygon(std::vector<Vec2F>{
        Vec2F(0.f, 0.f),
        Vec2F(4.f, 4.f),
        Vec2F(0.f, 4.f)
    });
    RectangleF rectangle(Vec2F(1.f, 1.f), Vec2F(2.f, 2.f));
    RectangleF rectangleIntersect(Vec2F(1.f, 1.f), Vec2F(3.f, 3.f));
    RectangleF rectangleNotIntersect(Vec2F(10.f, 20.f), Vec2F(20.f, 30.f));

    EXPECT_TRUE(Intersect(polygon, rectangle));
    EXPECT_TRUE(Intersect(polygon, rectangleIntersect));
    EXPECT_FALSE(Intersect(polygon, rectangleNotIntersect));
}