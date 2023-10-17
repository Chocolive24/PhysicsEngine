/**
 * @brief Unit tests for Vec4 class
 * @author Alexis
*/

#include "Vec4.h"

#include "gtest/gtest.h"

using namespace Math;

constexpr int ValuesSize = 30;

enum numberType
{
    Positive, Negative, Mixed, Time
};

template <typename T>
T* GenerateValues(numberType type, bool reverseOrder = false)
{
    auto* list = new T[ValuesSize];

    for (int i = 1; i < ValuesSize + 1; i++)
    {
        T number = 0;
        int j = reverseOrder ? ValuesSize - i + 1 : i;

        switch (type)
        {
            case Positive: number = j; break;
            case Negative: number = -j; break;
            case Mixed: number = j % 2 == 0 ? j : -j; break;
            case Time: number = static_cast<float>(j) / static_cast<float>(ValuesSize); break;
        }

        list[i - 1] = number;
    }

    return list;
}

template <typename T>
Vec4<T>* GenerateVectors(numberType type, bool reverseOrder = false)
{
    auto* list = new Vec4<T>[ValuesSize];
    auto* values = GenerateValues<T>(type);
    auto* values2 = GenerateValues<T>(type, true);

    for (int i = 0; i < ValuesSize; i++)
    {
        const auto index = reverseOrder ? ValuesSize - i - 1 : i;

        list[i] = Vec4<T>(values[index], values2[index], -values[index], -values2[index]);
    }

    delete[] values;
    delete[] values2;

    return list;
}

struct FloatTestFixtureMixed : public ::testing::TestWithParam<float*> {};
struct IntTestFixtureMixed : public ::testing::TestWithParam<int*> {};
// Vec4F
struct Vec4FTestFixtureMixedPair : public ::testing::TestWithParam<std::pair<Vec4F*, Vec4F*>> {};
struct Vec4FTestFixtureMixedPairWithScalar : public ::testing::TestWithParam<std::pair<std::pair<Vec4F*, Vec4F*>, float*>> {};
struct Vec4FTestFixtureMixedVec : public ::testing::TestWithParam<Vec4F*> {};
struct Vec4FTestFixtureMixedPairWithTime : public ::testing::TestWithParam<std::pair<std::pair<Vec4F*, Vec4F*>, float*>> {};
// Vec4I
struct Vec4ITestFixtureMixedPair : public ::testing::TestWithParam<std::pair<Vec4I*, Vec4I*>> {};
struct Vec4ITestFixtureMixedPairWithScalar : public ::testing::TestWithParam<std::pair<std::pair<Vec4I*, Vec4I*>, int*>> {};
struct Vec4ITestFixtureMixedVec : public ::testing::TestWithParam<Vec4I*> {};
struct Vec4ITestFixtureMixedPairWithTime : public ::testing::TestWithParam<std::pair<std::pair<Vec4I*, Vec4I*>, float*>> {};

INSTANTIATE_TEST_SUITE_P(Float, FloatTestFixtureMixed, testing::Values(GenerateValues<float>(Mixed)));
INSTANTIATE_TEST_SUITE_P(Int, IntTestFixtureMixed, testing::Values(GenerateValues<int>(Mixed)));

INSTANTIATE_TEST_SUITE_P(Vec4F, Vec4FTestFixtureMixedPair, testing::Values(std::pair(GenerateVectors<float>(Mixed),GenerateVectors<float>(Mixed, true))));
INSTANTIATE_TEST_SUITE_P(Vec4F, Vec4FTestFixtureMixedPairWithScalar, testing::Values(std::pair(std::pair(GenerateVectors<float>(Mixed), GenerateVectors<float>(Mixed, true)), GenerateValues<float>(Mixed))));
INSTANTIATE_TEST_SUITE_P(Vec4F, Vec4FTestFixtureMixedVec, testing::Values(GenerateVectors<float>(Mixed)));
INSTANTIATE_TEST_SUITE_P(Vec4F, Vec4FTestFixtureMixedPairWithTime, testing::Values(std::pair(std::pair(GenerateVectors<float>(Mixed), GenerateVectors<float>(Mixed, true)), GenerateValues<float>(Time))));

INSTANTIATE_TEST_SUITE_P(Vec4I, Vec4ITestFixtureMixedPair, testing::Values(std::pair(GenerateVectors<int>(Mixed),GenerateVectors<int>(Mixed, true))));
INSTANTIATE_TEST_SUITE_P(Vec4I, Vec4ITestFixtureMixedPairWithScalar, testing::Values(std::pair(std::pair(GenerateVectors<int>(Mixed), GenerateVectors<int>(Mixed, true)), GenerateValues<int>(Mixed))));
INSTANTIATE_TEST_SUITE_P(Vec4I, Vec4ITestFixtureMixedVec, testing::Values(GenerateVectors<int>(Mixed)));
INSTANTIATE_TEST_SUITE_P(Vec4I, Vec4ITestFixtureMixedPairWithTime, testing::Values(std::pair(std::pair(GenerateVectors<int>(Mixed), GenerateVectors<int>(Mixed, true)), GenerateValues<float>(Time))));

TEST(Vec4, StaticVariables)
{
    EXPECT_EQ(Vec4<int>::Zero(), Vec4<int>(0, 0, 0, 0));
    EXPECT_EQ(Vec4<int>::One(), Vec4<int>(1, 1, 1, 1));
    EXPECT_EQ(Vec4<int>::Left(), Vec4<int>(-1, 0, 0, 0));
    EXPECT_EQ(Vec4<int>::Right(), Vec4<int>(1, 0, 0, 0));
    EXPECT_EQ(Vec4<int>::Up(), Vec4<int>(0, 1, 0, 0));
    EXPECT_EQ(Vec4<int>::Down(), Vec4<int>(0, -1, 0, 0));
    EXPECT_EQ(Vec4<int>::Forward(), Vec4<int>(0, 0, 1, 0));
    EXPECT_EQ(Vec4<int>::Backward(), Vec4<int>(0, 0, -1, 0));
}

#pragma region Vec4i

TEST_P(IntTestFixtureMixed, Constructors)
{
    const auto* values = GetParam();

    for (int i = 0; i < ValuesSize; i++)
    {
        Vec4<int> vec(values[i], values[i], -values[i], -values[i]);

        EXPECT_EQ(vec.X, values[i]);
        EXPECT_EQ(vec.Y, values[i]);
        EXPECT_EQ(vec.Z, -values[i]);
        EXPECT_EQ(vec.W, -values[i]);
    }
}

TEST_P(Vec4ITestFixtureMixedPair, OperatorPlus)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        const auto vec = value[i] + value2[i];
        auto vec2 = value[i];

        vec2 += value2[i];

        // + operator
        EXPECT_EQ(vec.X, value[i].X + value2[i].X);
        EXPECT_EQ(vec.Y, value[i].Y + value2[i].Y);
        EXPECT_EQ(vec.Z, value[i].Z + value2[i].Z);
        EXPECT_EQ(vec.W, value[i].W + value2[i].W);
        // += operator
        EXPECT_EQ(vec2.X, value[i].X + value2[i].X);
        EXPECT_EQ(vec2.Y, value[i].Y + value2[i].Y);
        EXPECT_EQ(vec2.Z, value[i].Z + value2[i].Z);
        EXPECT_EQ(vec2.W, value[i].W + value2[i].W);
    }
}

TEST_P(Vec4ITestFixtureMixedPair, OperatorMinus)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        const auto vec = value[i] - value2[i];
        auto vec2 = value[i];

        vec2 -= value2[i];

        // - operator
        EXPECT_EQ(vec.X, value[i].X - value2[i].X);
        EXPECT_EQ(vec.Y, value[i].Y - value2[i].Y);
        EXPECT_EQ(vec.Z, value[i].Z - value2[i].Z);
        EXPECT_EQ(vec.W, value[i].W - value2[i].W);
        // -= operator
        EXPECT_EQ(vec2.X, value[i].X - value2[i].X);
        EXPECT_EQ(vec2.Y, value[i].Y - value2[i].Y);
        EXPECT_EQ(vec2.Z, value[i].Z - value2[i].Z);
        EXPECT_EQ(vec2.W, value[i].W - value2[i].W);
        // - unary operator
        EXPECT_EQ((-value[i]).X, -value[i].X);
        EXPECT_EQ((-value[i]).Y, -value[i].Y);
        EXPECT_EQ((-value[i]).Z, -value[i].Z);
        EXPECT_EQ((-value[i]).W, -value[i].W);
    }
}

TEST_P(Vec4ITestFixtureMixedPairWithScalar, OperatorMultiply)
{
    const auto pairs = GetParam();
    auto* values = pairs.first.first;
    const auto* multipliers = pairs.first.second;
    const auto* scalars = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        const auto value = values[i];
        const auto multiplier = multipliers[i];
        int scalarValue = scalars[i];

        auto result = value;
        auto resultScalar = value;

        result *= multiplier;
        resultScalar *= scalarValue;

        // * operator with vec4
        EXPECT_EQ((value * multiplier).X, value.X * multiplier.X);
        EXPECT_EQ((value * multiplier).Y, value.Y * multiplier.Y);
        EXPECT_EQ((value * multiplier).Z, value.Z * multiplier.Z);
        EXPECT_EQ((value * multiplier).W, value.W * multiplier.W);
        // *= operator with vec4
        EXPECT_EQ(result.X, value.X * multiplier.X);
        EXPECT_EQ(result.Y, value.Y * multiplier.Y);
        EXPECT_EQ(result.Z, value.Z * multiplier.Z);
        EXPECT_EQ(result.W, value.W * multiplier.W);
        // * operator with scalar
        EXPECT_EQ((value * scalarValue).X, value.X * scalarValue);
        EXPECT_EQ((value * scalarValue).Y, value.Y * scalarValue);
        EXPECT_EQ((value * scalarValue).Z, value.Z * scalarValue);
        EXPECT_EQ((value * scalarValue).W, value.W * scalarValue);
        // *= operator with scalar
        EXPECT_EQ(resultScalar.X, value.X * scalarValue);
        EXPECT_EQ(resultScalar.Y, value.Y * scalarValue);
        EXPECT_EQ(resultScalar.Z, value.Z * scalarValue);
        EXPECT_EQ(resultScalar.W, value.W * scalarValue);
    }
}

TEST_P(Vec4ITestFixtureMixedPairWithScalar, OperatorDivide)
{
    const auto pairs = GetParam();
    auto* values = pairs.first.first;
    const auto* dividers = pairs.first.second;
    const auto* scalars = pairs.second;

    for (size_t i = 0; i < ValuesSize; i++)
    {
        const auto value = values[i];
        const auto divisor = dividers[i];
        const auto scalar = scalars[i];
        auto result = value;
        auto resultScalar = value;

        if (divisor.X == 0 || divisor.Y == 0 || divisor.Z == 0 || divisor.W == 0)
        {
            EXPECT_THROW(result / divisor, DivisionByZeroException);
            EXPECT_THROW(result /= divisor, DivisionByZeroException);
            continue;
        }

        if (scalar == 0)
        {
            EXPECT_THROW(resultScalar / scalar, DivisionByZeroException);
            EXPECT_THROW(resultScalar /= scalar, DivisionByZeroException);
            continue;
        }

        result /= divisor;
        resultScalar /= scalar;

        // / operator with vec4
        EXPECT_EQ((value / divisor).X, value.X / divisor.X);
        EXPECT_EQ((value / divisor).Y, value.Y / divisor.Y);
        EXPECT_EQ((value / divisor).Z, value.Z / divisor.Z);
        EXPECT_EQ((value / divisor).W, value.W / divisor.W);
        // /= operator with vec4
        EXPECT_EQ(result.X, value.X / divisor.X);
        EXPECT_EQ(result.Y, value.Y / divisor.Y);
        EXPECT_EQ(result.Z, value.Z / divisor.Z);
        EXPECT_EQ(result.W, value.W / divisor.W);
        // / operator with scalar
        EXPECT_EQ((value / scalar).X, value.X / scalar);
        EXPECT_EQ((value / scalar).Y, value.Y / scalar);
        EXPECT_EQ((value / scalar).Z, value.Z / scalar);
        EXPECT_EQ((value / scalar).W, value.W / scalar);
        // /= operator with scalar
        EXPECT_EQ(resultScalar.X, value.X / scalar);
        EXPECT_EQ(resultScalar.Y, value.Y / scalar);
        EXPECT_EQ(resultScalar.Z, value.Z / scalar);
        EXPECT_EQ(resultScalar.W, value.W / scalar);
    }
}

TEST_P(Vec4ITestFixtureMixedPair, OperatorEquality)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        EXPECT_EQ(value[i] == value2[i], value[i].X == value2[i].X && value[i].Y == value2[i].Y && value[i].Z == value2[i].Z && value[i].W == value2[i].W);
        EXPECT_EQ(value[i] != value2[i], value[i].X != value2[i].X || value[i].Y != value2[i].Y || value[i].Z != value2[i].Z || value[i].W != value2[i].W);
    }
}

TEST_P(Vec4ITestFixtureMixedVec, OperatorIndex)
{
    const auto* values = GetParam();

    for (int i = 0; i < ValuesSize; i++)
    {
        auto value = values[i];
        auto result = value.X;

        EXPECT_EQ(value[0], value.X);
        EXPECT_EQ(value[1], value.Y);
        EXPECT_EQ(value[2], value.Z);
        EXPECT_EQ(value[3], value.W);

        EXPECT_THROW(result = value[4], OutOfRangeException);
    }
}

TEST_P(Vec4ITestFixtureMixedVec, Abs)
{
    const auto* values = GetParam();

    for (int i = 0; i < ValuesSize; i++)
    {
        auto value = values[i];
        auto absValue = Vec4I::Abs(value);

        EXPECT_EQ(absValue.X, std::abs(value.X));
        EXPECT_EQ(absValue.Y, std::abs(value.Y));
        EXPECT_EQ(absValue.Z, std::abs(value.Z));
        EXPECT_EQ(absValue.W, std::abs(value.W));
    }
}

TEST_P(Vec4ITestFixtureMixedPair, Dot)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        EXPECT_EQ(Vec4I::Dot(value[i], value2[i]), value[i].X * value2[i].X + value[i].Y * value2[i].Y + value[i].Z * value2[i].Z + value[i].W * value2[i].W);
    }
}

TEST_P(Vec4ITestFixtureMixedVec, Length)
{
    const auto* values = GetParam();

    for (int i = 0; i < ValuesSize; i++)
    {
        auto value = values[i];
        auto length = std::sqrt(value.X * value.X + value.Y * value.Y + value.Z * value.Z + value.W * value.W);

        EXPECT_EQ(value.Length(), static_cast<int>(length));
    }
}

TEST_P(Vec4ITestFixtureMixedPairWithTime, Lerp)
{
    const auto pairs = GetParam();
    auto* value = pairs.first.first;
    const auto* value2 = pairs.first.second;
    const auto* times = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        auto vec = Vec4I::Lerp(value[i], value2[i], times[i]);
        auto vecLerp = value[i] + (value2[i] - value[i]) * times[i];

        EXPECT_EQ(vec, vecLerp);
    }
}

TEST_P(Vec4ITestFixtureMixedPair, Distance)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        auto distance = Vec4I::Distance(value[i], value2[i]);
        auto distance2 = (value[i] - value2[i]).Length();

        EXPECT_EQ(distance, distance2);
    }
}

#pragma endregion

#pragma region Vec4f

TEST_P(FloatTestFixtureMixed, Constructors)
{
    const auto* values = GetParam();

    for (int i = 0; i < ValuesSize; i++)
    {
        Vec4<float> vec(values[i], values[i], -values[i], -values[i]);

        EXPECT_EQ(vec.X, values[i]);
        EXPECT_EQ(vec.Y, values[i]);
        EXPECT_EQ(vec.Z, -values[i]);
        EXPECT_EQ(vec.W, -values[i]);
    }
}

TEST_P(Vec4FTestFixtureMixedPair, OperatorPlus)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        const auto vec = value[i] + value2[i];
        auto vec2 = value[i];

        vec2 += value2[i];

        // + operator
        EXPECT_EQ(vec.X, value[i].X + value2[i].X);
        EXPECT_EQ(vec.Y, value[i].Y + value2[i].Y);
        EXPECT_EQ(vec.Z, value[i].Z + value2[i].Z);
        EXPECT_EQ(vec.W, value[i].W + value2[i].W);
        // += operator
        EXPECT_EQ(vec2.X, value[i].X + value2[i].X);
        EXPECT_EQ(vec2.Y, value[i].Y + value2[i].Y);
        EXPECT_EQ(vec2.Z, value[i].Z + value2[i].Z);
        EXPECT_EQ(vec2.W, value[i].W + value2[i].W);
    }
}

TEST_P(Vec4FTestFixtureMixedPair, OperatorMinus)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        const auto vec = value[i] - value2[i];
        auto vec2 = value[i];

        vec2 -= value2[i];

        // - operator
        EXPECT_EQ(vec.X, value[i].X - value2[i].X);
        EXPECT_EQ(vec.Y, value[i].Y - value2[i].Y);
        EXPECT_EQ(vec.Z, value[i].Z - value2[i].Z);
        EXPECT_EQ(vec.W, value[i].W - value2[i].W);
        // -= operator
        EXPECT_EQ(vec2.X, value[i].X - value2[i].X);
        EXPECT_EQ(vec2.Y, value[i].Y - value2[i].Y);
        EXPECT_EQ(vec2.Z, value[i].Z - value2[i].Z);
        EXPECT_EQ(vec2.W, value[i].W - value2[i].W);
        // - unary operator
        EXPECT_EQ((-value[i]).X, -value[i].X);
        EXPECT_EQ((-value[i]).Y, -value[i].Y);
        EXPECT_EQ((-value[i]).Z, -value[i].Z);
        EXPECT_EQ((-value[i]).W, -value[i].W);
    }
}

TEST_P(Vec4FTestFixtureMixedPairWithScalar, OperatorMultiply)
{
    const auto pairs = GetParam();
    auto* values = pairs.first.first;
    const auto* multipliers = pairs.first.second;
    const auto* scalars = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        const auto value = values[i];
        const auto multiplier = multipliers[i];
        auto scalarValue = scalars[i];

        auto result = value;
        auto resultScalar = value;

        result *= multiplier;
        resultScalar *= scalarValue;

        // * operator with vec4
        EXPECT_EQ((value * multiplier).X, value.X * multiplier.X);
        EXPECT_EQ((value * multiplier).Y, value.Y * multiplier.Y);
        EXPECT_EQ((value * multiplier).Z, value.Z * multiplier.Z);
        EXPECT_EQ((value * multiplier).W, value.W * multiplier.W);
        // *= operator with vec4
        EXPECT_EQ(result.X, value.X * multiplier.X);
        EXPECT_EQ(result.Y, value.Y * multiplier.Y);
        EXPECT_EQ(result.Z, value.Z * multiplier.Z);
        EXPECT_EQ(result.W, value.W * multiplier.W);
        // * operator with scalar
        EXPECT_EQ((value * scalarValue).X, value.X * scalarValue);
        EXPECT_EQ((value * scalarValue).Y, value.Y * scalarValue);
        EXPECT_EQ((value * scalarValue).Z, value.Z * scalarValue);
        EXPECT_EQ((value * scalarValue).W, value.W * scalarValue);
        // *= operator with scalar
        EXPECT_EQ(resultScalar.X, value.X * scalarValue);
        EXPECT_EQ(resultScalar.Y, value.Y * scalarValue);
        EXPECT_EQ(resultScalar.Z, value.Z * scalarValue);
        EXPECT_EQ(resultScalar.W, value.W * scalarValue);
    }
}

TEST_P(Vec4FTestFixtureMixedPairWithScalar, OperatorDivide)
{
    const auto pairs = GetParam();
    auto* values = pairs.first.first;
    const auto* dividers = pairs.first.second;
    const auto* scalars = pairs.second;

    for (size_t i = 0; i < ValuesSize; i++)
    {
        const auto value = values[i];
        const auto divisor = dividers[i];
        const auto scalar = scalars[i];
        auto result = value;
        auto resultScalar = value;

        if (divisor.X == 0 || divisor.Y == 0)
        {
            EXPECT_THROW(result / divisor, DivisionByZeroException);
            EXPECT_THROW(result /= divisor, DivisionByZeroException);
            continue;
        }

        if (scalar == 0)
        {
            EXPECT_THROW(resultScalar / scalar, DivisionByZeroException);
            EXPECT_THROW(resultScalar /= scalar, DivisionByZeroException);
            continue;
        }

        result /= divisor;
        resultScalar /= scalar;

        // / operator with vec4
        EXPECT_EQ((value / divisor).X, value.X / divisor.X);
        EXPECT_EQ((value / divisor).Y, value.Y / divisor.Y);
        EXPECT_EQ((value / divisor).Z, value.Z / divisor.Z);
        EXPECT_EQ((value / divisor).W, value.W / divisor.W);
        // /= operator with vec4
        EXPECT_EQ(result.X, value.X / divisor.X);
        EXPECT_EQ(result.Y, value.Y / divisor.Y);
        EXPECT_EQ(result.Z, value.Z / divisor.Z);
        EXPECT_EQ(result.W, value.W / divisor.W);
        // / operator with scalar
        EXPECT_EQ((value / scalar).X, value.X / scalar);
        EXPECT_EQ((value / scalar).Y, value.Y / scalar);
        EXPECT_EQ((value / scalar).Z, value.Z / scalar);
        EXPECT_EQ((value / scalar).W, value.W / scalar);
        // /= operator with scalar
        EXPECT_EQ(resultScalar.X, value.X / scalar);
        EXPECT_EQ(resultScalar.Y, value.Y / scalar);
        EXPECT_EQ(resultScalar.Z, value.Z / scalar);
        EXPECT_EQ(resultScalar.W, value.W / scalar);
    }
}

TEST_P(Vec4FTestFixtureMixedPair, OperatorEquality)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        EXPECT_EQ(value[i] == value2[i], value[i].X == value2[i].X && value[i].Y == value2[i].Y && value[i].Z == value2[i].Z && value[i].W == value2[i].W);
        EXPECT_EQ(value[i] != value2[i], value[i].X != value2[i].X || value[i].Y != value2[i].Y || value[i].Z != value2[i].Z || value[i].W != value2[i].W);
    }
}

TEST_P(Vec4FTestFixtureMixedVec, OperatorIndex)
{
    const auto* values = GetParam();

    for (int i = 0; i < ValuesSize; i++)
    {
        auto value = values[i];
        auto result = value.X;

        EXPECT_EQ(value[0], value.X);
        EXPECT_EQ(value[1], value.Y);
        EXPECT_EQ(value[2], value.Z);
        EXPECT_EQ(value[3], value.W);

        EXPECT_THROW(result = value[4], OutOfRangeException);
    }
}

TEST_P(Vec4FTestFixtureMixedVec, Abs)
{
    const auto* values = GetParam();

    for (int i = 0; i < ValuesSize; i++)
    {
        auto value = values[i];
        auto absValue = Vec4F::Abs(value);

        EXPECT_EQ(absValue.X, std::abs(value.X));
        EXPECT_EQ(absValue.Y, std::abs(value.Y));
        EXPECT_EQ(absValue.Z, std::abs(value.Z));
        EXPECT_EQ(absValue.W, std::abs(value.W));
    }
}

TEST_P(Vec4FTestFixtureMixedPair, Dot)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        EXPECT_EQ(Vec4F::Dot(value[i], value2[i]), value[i].X * value2[i].X + value[i].Y * value2[i].Y + value[i].Z * value2[i].Z + value[i].W * value2[i].W);
    }
}

TEST_P(Vec4FTestFixtureMixedVec, Length)
{
    const auto* values = GetParam();

    for (int i = 0; i < ValuesSize; i++)
    {
        auto value = values[i];
        auto length = std::sqrt(value.X * value.X + value.Y * value.Y + value.Z * value.Z + value.W * value.W);

        EXPECT_FLOAT_EQ(value.Length(), length);
    }
}

TEST_P(Vec4FTestFixtureMixedPairWithTime, Lerp)
{
    const auto pairs = GetParam();
    auto* value = pairs.first.first;
    const auto* value2 = pairs.first.second;
    const auto* times = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        auto vec = Vec4F::Lerp(value[i], value2[i], times[i]);
        auto vecLerp = value[i] + (value2[i] - value[i]) * times[i];

        EXPECT_EQ(vec, vecLerp);
    }
}

TEST_P(Vec4FTestFixtureMixedPair, Distance)
{
    const auto pairs = GetParam();
    auto* value = pairs.first;
    const auto* value2 = pairs.second;

    for (int i = 0; i < ValuesSize; i++)
    {
        auto distance = Vec4F::Distance(value[i], value2[i]);
        auto distance2 = (value[i] - value2[i]).Length();

        EXPECT_FLOAT_EQ(distance, distance2);
    }
}

#pragma endregion