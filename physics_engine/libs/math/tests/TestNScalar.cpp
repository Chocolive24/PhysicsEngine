/**
 * @author Rémy
 */

#include "NScalar.h"
#include "Vec2.h"

#include "gtest/gtest.h"

using namespace Math;

struct FourScalarFTestFixtureMixed : public ::testing::TestWithParam<std::pair<FourScalarF, FourScalarF>>
{
};
struct FourScalarITestFixtureMixed : public ::testing::TestWithParam<std::pair<FourScalarI, FourScalarI>>
{
};

#pragma region InstantiateParametrizedTests

INSTANTIATE_TEST_SUITE_P(NScalar, FourScalarFTestFixtureMixed, testing::Values(
        std::make_pair(
                FourScalarF(std::array<float, 4>{1.4f, 2.5f, 3.6f, 4.7f}),
                FourScalarF(std::array<float, 4>{0, 2.5f, 6.9f, 8.11f})
        ),
        std::make_pair(
                FourScalarF(std::array<float, 4>{-1.4f, -2.5f, -3.6f, -4.7f}),
                FourScalarF(std::array<float, 4>{6.f, -2.5f, -6.9f, -8.11f})
        )
));

INSTANTIATE_TEST_SUITE_P(NScalar, FourScalarITestFixtureMixed, testing::Values(
        std::make_pair(
                FourScalarI(std::array<int, 4>{1, 2, 7, 8}),
                FourScalarI(std::array<int, 4>{10, 2, 0, 4})
        ),
        std::make_pair(
                FourScalarI(std::array<int, 4>{-1, -2, -7, -8}),
                FourScalarI(std::array<int, 4>{-10, -2, 8, -4})
        )
));

#pragma endregion

TEST(FourScalarITest, Creation)
{
    std::array<int, 4> values = {1, 0, 2, 3};
    Math::FourScalarI nS(values);

    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nS[i], values[i]);
    }

    Math::FourScalarI nS2(2);
    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nS2[i], 2);
    }
}

TEST(FourScalarFTest, Creation)
{
    std::array<float, 4> values = {1.5f, 0.0f, 2.8f, 33.4f};
    Math::FourScalarF nS(values);

    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nS[i], values[i]);
    }

    Math::FourScalarF nS2(54.4f);
    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nS2[i], 54.4f);
    }
}


TEST_P(FourScalarFTestFixtureMixed, OperatorPlus)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 + nV2;
    auto result2 = nV1;
    result2 += nV2;

    for (int i = 0; i < 4; i++)
    {
        // +
        EXPECT_EQ(result[i], nV1[i] + nV2[i]);
        // +=
        EXPECT_EQ(result2[i], nV1[i] + nV2[i]);
        EXPECT_EQ(result2[i], nV1[i] + nV2[i]);
    }
}

TEST_P(FourScalarFTestFixtureMixed, OperatorMinus)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 - nV2;
    auto result2 = nV1;
    result2 -= nV2;
    auto result3 = -nV1;

    for (int i = 0; i < 4; i++)
    {
        // -
        EXPECT_EQ(result[i], nV1[i] - nV2[i]);
        // -=
        EXPECT_EQ(result2[i], nV1[i] - nV2[i]);
        // - unary
        EXPECT_EQ(result3[i], -nV1[i]);
    }
}

TEST_P(FourScalarFTestFixtureMixed, OperatorMultiply)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 * nV2;
    auto result2 = nV1;
    result2 *= nV2;

    for (int i = 0; i < 4; i++)
    {
        // *
        EXPECT_EQ(result[i], nV1[i] * nV2[i]);
        // *=
        EXPECT_EQ(result2[i], nV1[i] * nV2[i]);
    }
}

TEST_P(FourScalarFTestFixtureMixed, OperatorDivide)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;
    constexpr auto epsilon = 0.0001f;

    for (int i = 0; i < 4; i++)
    {
        if (nV2[i] == 0)
        {
            FourScalarF res;
            EXPECT_THROW(res = nV1 / nV2, DivisionByZeroException);
            EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
            return;
        }
    }

    auto result = nV1 / nV2;
    auto result2 = nV1;
    result2 /= nV2;

    for (int i = 0; i < 4; i++)
    {
        // /
        EXPECT_NEAR(result[i], nV1[i] / nV2[i], epsilon);
        // /=
        EXPECT_NEAR(result2[i], nV1[i] / nV2[i], epsilon);

    }
}

TEST_P(FourScalarITestFixtureMixed, OperatorPlus)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 + nV2;
    auto result2 = nV1;
    result2 += nV2;

    for (int i = 0; i < 4; i++)
    {
        // +
        EXPECT_EQ(result[i], nV1[i] + nV2[i]);
        // +=
        EXPECT_EQ(result2[i], nV1[i] + nV2[i]);
        EXPECT_EQ(result2[i], nV1[i] + nV2[i]);
    }
}

TEST_P(FourScalarITestFixtureMixed, OperatorMinus)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 - nV2;
    auto result2 = nV1;
    result2 -= nV2;
    auto result3 = -nV1;

    for (int i = 0; i < 4; i++)
    {
        // -
        EXPECT_EQ(result[i], nV1[i] - nV2[i]);
        // -=
        EXPECT_EQ(result2[i], nV1[i] - nV2[i]);
        // - unary
        EXPECT_EQ(result3[i], -nV1[i]);
    }
}

TEST_P(FourScalarITestFixtureMixed, OperatorMultiply)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 * nV2;
    auto result2 = nV1;
    result2 *= nV2;

    for (int i = 0; i < 4; i++)
    {
        // *
        EXPECT_EQ(result[i], nV1[i] * nV2[i]);
        // *=
        EXPECT_EQ(result2[i], nV1[i] * nV2[i]);
    }
}

TEST_P(FourScalarITestFixtureMixed, OperatorDivide)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;
    constexpr auto epsilon = 0.0001f;

    for (int i = 0; i < 4; i++)
    {
        if (nV2[i] == 0 )
        {
            FourScalarI res;
            EXPECT_THROW(res = nV1 / nV2, DivisionByZeroException);
            EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
            return;
        }
    }

    auto result = nV1 / nV2;
    auto result2 = nV1;
    result2 /= nV2;

    for (int i = 0; i < 4; i++)
    {
        // /
        EXPECT_NEAR(result[i], nV1[i] / nV2[i], epsilon);
        // /=
        EXPECT_NEAR(result2[i], nV1[i] / nV2[i], epsilon);
    }
}