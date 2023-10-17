/**
* @headerfile Test the Angle.h classes and functions
* @author Alexis Haldy
*/

#include "gtest/gtest.h"
#include "Angle.h"
#include "Exception.h"

const size_t Size = 720;

float* GetAngles(bool reverseOrder = false)
{
    auto* values = new float[Size];

    for (int i = 0; i < Size; i++)
    {
        if (reverseOrder)
        {
            values[i] = (Size - i) / 2.f;
        }
        else
        {
            values[i] = i / 2.f;
        }
    }

    return values;
}

template <typename T>
T* GenerateValues(bool reverseOrder = false)
{
    auto* list = new T[Size];

    for (std::size_t i = 1; i < Size + 1; i++)
    {
        int j = reverseOrder ? Size - static_cast<int>(i) + 1 : i;

        list[i - 1] = j % 2 == 0 ? j : -j;
    }

    return list;
}

struct AngleTestFixtureMixed : public ::testing::TestWithParam<float*> {};
struct AngleTestFixtureMixedPair : public ::testing::TestWithParam<std::pair<float*, float*>> {};
struct AngleTestFixtureMixedWithScalars : public ::testing::TestWithParam<std::pair<float*, float*>> {};

INSTANTIATE_TEST_SUITE_P(Float, AngleTestFixtureMixed, testing::Values(GetAngles()));
INSTANTIATE_TEST_SUITE_P(Float, AngleTestFixtureMixedPair, testing::Values(std::make_pair(GetAngles(), GetAngles(true))));
INSTANTIATE_TEST_SUITE_P(Float, AngleTestFixtureMixedWithScalars, testing::Values(std::make_pair(GetAngles(), GenerateValues<float>())));

#pragma region Degree

TEST_P(AngleTestFixtureMixed, DegreeConstructor)
{
    auto values = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Degree degree(values[i]);

        EXPECT_FLOAT_EQ(static_cast<float>(degree), values[i]);
    }
}

TEST_P(AngleTestFixtureMixedPair, DegreeOperatorPlus)
{
    auto values = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Degree degree(values.first[i]);
        Math::Degree degree2(values.second[i]);
        Math::Degree result = degree;

        result += degree2;

        EXPECT_FLOAT_EQ(static_cast<float>(degree + degree2), values.first[i] + values.second[i]);
        EXPECT_FLOAT_EQ(static_cast<float>(result), values.first[i] + values.second[i]);
    }
}

TEST_P(AngleTestFixtureMixedPair, DegreeOperatorMinus)
{
    auto values = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Degree degree(values.first[i]);
        Math::Degree degree2(values.second[i]);
        Math::Degree result = degree;

        result -= degree2;

        EXPECT_FLOAT_EQ(static_cast<float>(degree - degree2), values.first[i] - values.second[i]);
        EXPECT_FLOAT_EQ(static_cast<float>(result), values.first[i] - values.second[i]);
        EXPECT_FLOAT_EQ(static_cast<float>(-degree), -values.first[i]);
    }
}

TEST_P(AngleTestFixtureMixedWithScalars, DegreeOperatorMultiply)
{
    const auto pairs = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Degree degree(pairs.first[i]);
        float scalar = pairs.second[i];
        Math::Degree result = degree;

        result *= scalar;

        EXPECT_FLOAT_EQ(static_cast<float>(degree * scalar), pairs.first[i] * scalar);
        EXPECT_FLOAT_EQ(static_cast<float>(result), pairs.first[i] * scalar);
    }
}

TEST_P(AngleTestFixtureMixedWithScalars, DegreeOperatorDivide)
{
    const auto pairs = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Degree degree(pairs.first[i]);
        float scalar = pairs.second[i];
        Math::Degree result = degree;

        if (scalar == 0)
        {
            Math::Degree res;
            EXPECT_THROW(res = result / scalar, DivisionByZeroException);
            EXPECT_THROW(result /= scalar, DivisionByZeroException);
            continue;
        }

        result /= scalar;

        EXPECT_FLOAT_EQ(static_cast<float>(degree / scalar), pairs.first[i] / scalar);
        EXPECT_FLOAT_EQ(static_cast<float>(result), pairs.first[i] / scalar);
    }
}

TEST_P(AngleTestFixtureMixedPair, DegreeOperatorEqualities)
{
    auto values = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Degree degree(values.first[i]);
        Math::Degree degree2(values.second[i]);

        EXPECT_EQ(degree == degree2, values.first[i] == values.second[i]);
        EXPECT_EQ(degree != degree2, values.first[i] != values.second[i]);
        EXPECT_EQ(degree <= degree2, values.first[i] <= values.second[i]);
        EXPECT_EQ(degree >= degree2, values.first[i] >= values.second[i]);
        EXPECT_EQ(degree < degree2, values.first[i] < values.second[i]);
        EXPECT_EQ(degree > degree2, values.first[i] > values.second[i]);
    }
}

#pragma endregion // Degree

#pragma region Radian

TEST_P(AngleTestFixtureMixed, RadianConstructor)
{
    auto values = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Radian radian(values[i]);

        EXPECT_FLOAT_EQ(static_cast<float>(radian), values[i]);
    }
}

TEST_P(AngleTestFixtureMixedPair, RadianOperatorPlus)
{
    auto values = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Radian radian(values.first[i]);
        Math::Radian radian2(values.second[i]);
        Math::Radian result = radian;

        result += radian2;

        EXPECT_FLOAT_EQ(static_cast<float>(radian + radian2), values.first[i] + values.second[i]);
        EXPECT_FLOAT_EQ(static_cast<float>(result), values.first[i] + values.second[i]);
    }
}

TEST_P(AngleTestFixtureMixedPair, RadianOperatorMinus)
{
    auto values = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Radian radian(values.first[i]);
        Math::Radian radian2(values.second[i]);
        Math::Radian result = radian;

        result -= radian2;

        EXPECT_FLOAT_EQ(static_cast<float>(radian - radian2), values.first[i] - values.second[i]);
        EXPECT_FLOAT_EQ(static_cast<float>(result), values.first[i] - values.second[i]);
        EXPECT_FLOAT_EQ(static_cast<float>(-radian), -values.first[i]);
    }
}

TEST_P(AngleTestFixtureMixedWithScalars, RadianOperatorMultiply)
{
    const auto pairs = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Radian radian(pairs.first[i]);
        float scalar = pairs.second[i];
        Math::Radian result = radian;

        result *= scalar;

        EXPECT_FLOAT_EQ(static_cast<float>(radian * scalar), pairs.first[i] * scalar);
        EXPECT_FLOAT_EQ(static_cast<float>(result), pairs.first[i] * scalar);
    }
}

TEST_P(AngleTestFixtureMixedWithScalars, RadianOperatorDivide)
{
    const auto pairs = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Radian radian(pairs.first[i]);
        float scalar = pairs.second[i];
        Math::Radian result = radian;

        if (scalar == 0)
        {
            Math::Radian res;
            EXPECT_THROW(res = result / scalar, DivisionByZeroException);
            EXPECT_THROW(result /= scalar, DivisionByZeroException);
            continue;
        }

        result /= scalar;

        EXPECT_FLOAT_EQ(static_cast<float>(radian / scalar), pairs.first[i] / scalar);
        EXPECT_FLOAT_EQ(static_cast<float>(result), pairs.first[i] / scalar);
    }
}

TEST_P(AngleTestFixtureMixedPair, RadianOperatorEqualities)
{
    auto values = GetParam();

    for (int i = 0; i < Size; i++)
    {
        Math::Radian radian(values.first[i]);
        Math::Radian radian2(values.second[i]);

        EXPECT_EQ(radian == radian2, values.first[i] == values.second[i]);
        EXPECT_EQ(radian != radian2, values.first[i] != values.second[i]);
        EXPECT_EQ(radian <= radian2, values.first[i] <= values.second[i]);
        EXPECT_EQ(radian >= radian2, values.first[i] >= values.second[i]);
        EXPECT_EQ(radian < radian2, values.first[i] < values.second[i]);
        EXPECT_EQ(radian > radian2, values.first[i] > values.second[i]);
    }
}

#pragma endregion // Radian