/**
* @headerfile Test the Random.h classes and functions
* @author Alexis
*/

#include "Random.h"

#include "gtest/gtest.h"

struct IntTestFixturePair : public ::testing::TestWithParam<std::pair<int, int>> {};
struct FloatTestFixturePair : public ::testing::TestWithParam<std::pair<float, float>> {};

INSTANTIATE_TEST_SUITE_P(Random, IntTestFixturePair, testing::Values(
    std::make_pair(0, 10),
    std::make_pair(10, 0),
    std::make_pair(-10, 10),
    std::make_pair(10, -10),
    std::make_pair(-10, -5),
    std::make_pair(-5, -10),
    std::make_pair(0, 0)
));

INSTANTIATE_TEST_SUITE_P(Random, FloatTestFixturePair, testing::Values(
    std::make_pair(0.0f, 10.0f),
    std::make_pair(10.0f, 0.0f),
    std::make_pair(-10.0f, 10.0f),
    std::make_pair(10.0f, -10.0f),
    std::make_pair(-10.0f, -5.0f),
    std::make_pair(-5.0f, -10.0f),
    std::make_pair(0.0f, 0.0f)
));

TEST_P(IntTestFixturePair, Range)
{
    std::pair<int, int> p = GetParam();

    int min = p.first;
    int max = p.second;

    int result = Math::Random::Range(min, max);

    if (min < max)
    {
        EXPECT_GE(result, min);
        EXPECT_LE(result, max);
    }
    else if (min == max)
    {
        EXPECT_EQ(result, min);
    }
    else
    {
        EXPECT_GE(result, max);
        EXPECT_LE(result, min);
    }
}

TEST_P(FloatTestFixturePair, Range)
{
    std::pair<float, float> p = GetParam();

    float min = p.first;
    float max = p.second;

    float result = Math::Random::Range(min, max);

    if (min < max)
    {
        EXPECT_GE(result, min);
        EXPECT_LE(result, max);
    }
    else if (min == max)
    {
        EXPECT_EQ(result, min);
    }
    else
    {
        EXPECT_GE(result, max);
        EXPECT_LE(result, min);
    }
}