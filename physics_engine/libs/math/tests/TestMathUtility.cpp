/**
 * @brief Unit tests for MathUtility functions
 * @author Alexis, Olivier, Constantin, Remy
 */

#include "gtest/gtest.h"
#include "MathUtility.h"

Radian* GetAngles()
{
    auto* angles = new Radian[720];

    for (int i = 0; i < 720; i++)
    {
        angles[i] = Radian(Degree(i / 2.f));
    }

    return angles;
}

Radian* GetAnglesInTanRange()
{
    auto* angles = new Radian[160];

    for (int i = -80; i < 80; i++)
    {
        int index = i + 80;
        angles[index] = Radian(Degree(static_cast<float>(i)));
    }

    return angles;
}

struct RadianTestFixture: public ::testing::TestWithParam<Radian*> {};

struct RadianInTanRangeTestFixture : public ::testing::TestWithParam<Radian*> {};

INSTANTIATE_TEST_SUITE_P(Float, RadianTestFixture, testing::Values(GetAngles()));

INSTANTIATE_TEST_SUITE_P(Float, RadianInTanRangeTestFixture, testing::Values(GetAnglesInTanRange()));

struct FunctionsFixture : public ::testing::TestWithParam<float>
{
};

INSTANTIATE_TEST_SUITE_P(MathUtility, FunctionsFixture, testing::Values(
        1, 2.2, 3.3, 4, 5, 2, 4, 8, 22, 50, 56, 65, 87, 0.0001f, 1.25f, 30, 50, 0.001f, 720, 125
));


TEST_P(FunctionsFixture, Abs){
    auto values = FunctionsFixture::GetParam();
    EXPECT_EQ(MathUtility::Abs<int>(-1 * static_cast<int>(values)), static_cast<int>(values));
    EXPECT_EQ(MathUtility::Abs<int>(static_cast<int>(values)),  static_cast<int>(values));
    EXPECT_EQ(MathUtility::Abs<int>(0), 0);

    EXPECT_EQ(MathUtility::Abs<float>(-1 * values), values);
    EXPECT_EQ(MathUtility::Abs<float>(values), values);
}

TEST_P(FunctionsFixture, Clamp)
{
    auto values = FunctionsFixture::GetParam();
    auto result = values;
    if (values < 0)
    {
        result = 0;
    }
    else if (values > 10)
    {
        result = 10;
    }
    EXPECT_EQ(MathUtility::Clamp<int>(static_cast<int>(values), 0, 10), static_cast<int>(result));

    if (values < 0.f)
    {
        result = 0;
    }
    else if (values > 0.0001f)
    {
        result = 0.0001f;
    }
    EXPECT_FLOAT_EQ(MathUtility::Clamp<float>(values, 0.0001f, 0.f), result);
}

TEST_P(FunctionsFixture, Min)
{
    auto values = FunctionsFixture::GetParam();
    auto result = values < 20 ? values : 20;
    EXPECT_EQ(MathUtility::Min<int>(static_cast<int>(values), 20), static_cast<int>(result));
    EXPECT_EQ(MathUtility::Min<int>(20, static_cast<int>(values)), static_cast<int>(result));
    EXPECT_EQ(MathUtility::Min<int>(-0, 0), -0);
    result = values < 0.001f ? values : 0.001f;
    EXPECT_FLOAT_EQ(MathUtility::Min<float>(values, 0.001f), result);
}

TEST_P(FunctionsFixture, Max)
{
    auto values = FunctionsFixture::GetParam();
    auto result = values > 20 ? 20 : values;
    EXPECT_EQ(MathUtility::Min<int>(static_cast<int>(values), 20), static_cast<int>(result));
    EXPECT_EQ(MathUtility::Min<int>(20, static_cast<int>(values)), static_cast<int>(result));
    EXPECT_EQ(MathUtility::Min<int>(-0, 0), -0);
    result = values > 0.001f ? 0.001f : values;
    EXPECT_FLOAT_EQ(MathUtility::Min<float>(values, 0.001f), result);
}

TEST_P(FunctionsFixture, Factorial)
{
    auto values = FunctionsFixture::GetParam();
    auto result = 1;

    for (int i = 2; i <= MathUtility::Abs(values); i++)
    {
        result *= i;
    }

    if (values < 0)
    {
        result = -result;
    }

    EXPECT_EQ(MathUtility::Fact<int>(0), 1);
    EXPECT_EQ(MathUtility::Fact<int>(static_cast<int>(values)), static_cast<int>(result));
    EXPECT_FLOAT_EQ(MathUtility::Fact<int>(values), result);
}

TEST_P(FunctionsFixture, PowInt)
{
    int values = static_cast<int>(FunctionsFixture::GetParam());
    auto result = 1;
    int power = 5;
    for (int i = 1; i <= power; i++)
    {
        result *= values;
    }
    if (values == 0)
    {
        result = 0;
    }
    EXPECT_EQ(MathUtility::Pow<int>(values, 5), result);
}

TEST_P(FunctionsFixture, PowFloat)
{
    auto values = FunctionsFixture::GetParam();
    float result = 1;
    int power = 5;
    for (int i = 1; i <= power; i++)
    {
        result *= values;
    }
    if (values == 0)
    {
        result = 0;
    }
    EXPECT_FLOAT_EQ(MathUtility::Pow<float>(values, 5), result);
}


TEST_P(RadianTestFixture, Sin)
{
    constexpr float epsilon = 0.00001f;
    auto angles = GetParam();

    for (int i = 0; i < 720; i++)
    {
        EXPECT_NEAR(MathUtility::Sin(angles[i]), std::sin(static_cast<float>(angles[i])), epsilon);
    }
}

TEST_P(RadianTestFixture, Cos)
{
    constexpr float epsilon = 0.00001f;
    auto angles = GetParam();

    for (int i = 0; i < 720; i++)
    {
        EXPECT_NEAR(MathUtility::Cos(angles[i]), std::cos(static_cast<float>(angles[i])), epsilon);
    }
}

TEST_P(RadianInTanRangeTestFixture, Tan)
{
    constexpr float epsilon = 0.001f;
    auto angles = GetParam();

    for (int i = 0; i < 160; i++)
    {
        EXPECT_NEAR(MathUtility::Tan(angles[i]), std::tan(static_cast<float>(angles[i])), epsilon);
    }
}


struct AngleFixture : public ::testing::TestWithParam<std::vector<Radian>>
{
};


std::vector<Radian> GetRadianAngles()
{
    std::vector<Radian> v;
    // Value to be withdrawn from the start and the end of the range, because tan isn't precise for values
    // too far from zero.
    int errorMargin = 12;
    v.reserve(CotTableSize - 2 * errorMargin);
    float value = MathUtility::CotRangeStart + static_cast<float>(errorMargin) * MathUtility::CotStepSize;
    for (int i = 0; i < CotTableSize - 2 * errorMargin; i++)
    {
        Radian r(value);
        v.push_back(r);
        value += MathUtility::CotStepSize;
    }
    return v;
}

INSTANTIATE_TEST_SUITE_P(Angles, AngleFixture, testing::Values(
        GetRadianAngles()
));

TEST_P(AngleFixture, CotWithLUT)
{
    auto angles = GetParam();
    for (auto a : angles)
    {
        EXPECT_NEAR(MathUtility::CotLut(a), 1/std::tan(static_cast<float>(a)), 0.001f);
    }
}