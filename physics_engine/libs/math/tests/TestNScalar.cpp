//
// Created by remla on 10/10/2023.
//

#include "gtest/gtest.h"
#include "NScalar.h"

struct EightScalarFTestFixture : public ::testing::TestWithParam<std::pair<EightScalarF, EightScalarF>>
{
};

struct FourScalarFTestFixtureMixed : public ::testing::TestWithParam<std::pair<FourScalarF, FourScalarF>>
{
};

struct EightScalarITestFixture : public ::testing::TestWithParam<std::pair<EightScalarI, EightScalarI>>
{
};

struct FourScalarITestFixtureMixed : public ::testing::TestWithParam<std::pair<FourScalarI, FourScalarI>>
{
};

#pragma region InstantiateParametrizedTests

INSTANTIATE_TEST_SUITE_P(NScalar, EightScalarFTestFixture, testing::Values(
        std::make_pair(
                EightScalarF(std::array<float, 8>{
                        1.3f, 3.5f, 5.7f, 7.9f, 9.11f, 11.13f, 14.16f, 16.18f
                }),
                EightScalarF(std::array<float, 8>{
                        10.3f, 32.5f, 54.7f, 8.10f, 1.1f, 10.12f, 111.13f, 12.14f
                }))
));

INSTANTIATE_TEST_SUITE_P(NScalar, FourScalarFTestFixtureMixed, testing::Values(
        std::make_pair(
                FourScalarF(std::array<float, 4>{1.4f, 2.5f, 3.6f, 4.7f}),
                FourScalarF(std::array<float, 4>{0, 2.5f, 6.9f, 8.11f})
        )
));

INSTANTIATE_TEST_SUITE_P(NScalar, EightScalarITestFixture, testing::Values(
        std::make_pair(
                EightScalarI(std::array<int, 8>{
                        1, 3, 5, 7, 9, 11, 14, 16
                }),
                EightScalarI(std::array<int, 8>{
                        10, 32, 6, 8, 98, 10, 14, 16
                })
        )
));

INSTANTIATE_TEST_SUITE_P(NScalar, FourScalarITestFixtureMixed, testing::Values(
        std::make_pair(
                FourScalarI(std::array<int, 4>{1, 2, 7, 8}),
                FourScalarI(std::array<int, 4>{10, 2, 0, 4})
        )
));


TEST_P(EightScalarFTestFixture, OperatorPlus)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 + nV2;
    auto result2 = nV1;
    result2 += nV2;

    for (int i = 0; i < 8; i++)
    {
        // +
        EXPECT_EQ(result[i], nV1[i] + nV2[i]);
        // +=
        EXPECT_EQ(result2[i], nV1[i] + nV2[i]);
        EXPECT_EQ(result2[i], nV1[i] + nV2[i]);
    }
}

TEST_P(EightScalarFTestFixture, OperatorMinus)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 - nV2;
    auto result2 = nV1;
    result2 -= nV2;
    auto result3 = -nV1;

    for (int i = 0; i < 8; i++)
    {
        // -
        EXPECT_EQ(result[i], nV1[i] - nV2[i]);
        // -=
        EXPECT_EQ(result2[i], nV1[i] - nV2[i]);
        // - unary
        EXPECT_EQ(result3[i], -nV1[i]);
    }
}

TEST_P(EightScalarFTestFixture, OperatorMultiply)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 * nV2;
    auto result2 = nV1;
    result2 *= nV2;

    for (int i = 0; i < 8; i++)
    {
        // *
        EXPECT_EQ(result[i], nV1[i] * nV2[i]);
        // *=
        EXPECT_EQ(result2[i], nV1[i] * nV2[i]);
    }
}

TEST_P(EightScalarFTestFixture, OperatorDivide)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;
    constexpr auto epsilon = 0.0001f;

    for (int i = 0; i < 8; i++)
    {
        if (nV2[i] == 0 )
        {
            EXPECT_THROW(nV1 / nV2, DivisionByZeroException);
            EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
            return;
        }
    }

    auto result = nV1 / nV2;
    auto result2 = nV1;
    result2 /= nV2;

    for (int i = 0; i < 8; i++)
    {
        // /
        EXPECT_NEAR(result[i], nV1[i] / nV2[i], epsilon);
        // /=
        EXPECT_NEAR(result2[i], nV1[i] / nV2[i], epsilon);

    }
}

TEST_P(EightScalarITestFixture, OperatorPlus)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 + nV2;
    auto result2 = nV1;
    result2 += nV2;

    for (int i = 0; i < 8; i++)
    {
        // +
        EXPECT_EQ(result[i], nV1[i] + nV2[i]);
        // +=
        EXPECT_EQ(result2[i], nV1[i] + nV2[i]);
        EXPECT_EQ(result2[i], nV1[i] + nV2[i]);
    }
}

TEST_P(EightScalarITestFixture, OperatorMinus)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 - nV2;
    auto result2 = nV1;
    result2 -= nV2;
    auto result3 = -nV1;

    for (int i = 0; i < 8; i++)
    {
        // -
        EXPECT_EQ(result[i], nV1[i] - nV2[i]);
        // -=
        EXPECT_EQ(result2[i], nV1[i] - nV2[i]);
        // - unary
        EXPECT_EQ(result3[i], -nV1[i]);
    }
}

TEST_P(EightScalarITestFixture, OperatorMultiply)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;

    auto result = nV1 * nV2;
    auto result2 = nV1;
    result2 *= nV2;

    for (int i = 0; i < 8; i++)
    {
        // *
        EXPECT_EQ(result[i], nV1[i] * nV2[i]);
        // *=
        EXPECT_EQ(result2[i], nV1[i] * nV2[i]);
    }
}

TEST_P(EightScalarITestFixture, OperatorDivide)
{
    auto pair = GetParam();
    auto nV1 = pair.first;
    auto nV2 = pair.second;
    constexpr auto epsilon = 0.0001f;

    for (int i = 0; i < 8; i++)
    {
        if (nV2[i] == 0 )
        {
            EXPECT_THROW(nV1 / nV2, DivisionByZeroException);
            EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
            return;
        }
    }

    auto result = nV1 / nV2;
    auto result2 = nV1;
    result2 /= nV2;

    for (int i = 0; i < 8; i++)
    {
        // /
        EXPECT_NEAR(result[i], nV1[i] / nV2[i], epsilon);
        // /=
        EXPECT_NEAR(result2[i], nV1[i] / nV2[i], epsilon);

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
        if (nV2[i] == 0 )
        {
            EXPECT_THROW(nV1 / nV2, DivisionByZeroException);
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
            EXPECT_THROW(nV1 / nV2, DivisionByZeroException);
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