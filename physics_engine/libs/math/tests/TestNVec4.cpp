/**
 * @author Olivier
 */

#include "NVec4.h"

#include "gtest/gtest.h"

#include <array>

using namespace Math;

#pragma region Vec4 FixtureAndTestInstantations

struct OneVec4FloatFixture : public ::testing::TestWithParam<Vec4F>{};

struct OneVec4IntFixture : public ::testing::TestWithParam<Vec4I>{};

INSTANTIATE_TEST_SUITE_P(FourVec4F, OneVec4FloatFixture, testing::Values(
        Vec4F(1.f, 2.f, 3.f, 4.f),
        Vec4F(-11.55f, -2.4332f, -33.6789f, -4.000001f)
));

INSTANTIATE_TEST_SUITE_P(FourVec4I, OneVec4IntFixture, testing::Values(
        Vec4I(1, 2, 3, 4),
        Vec4I(-11, -2, -33, -4)
));

#pragma endregion Vec4 FixtureAndTestInstantations

#pragma region FourVec4 FixturesAndTestInstantations

struct ArrayOfFourVec4FloatFixture : public ::testing::TestWithParam<std::array<Vec4F, 4>> {};

struct ArrayOfFourVec4IntFixture : public ::testing::TestWithParam<std::array<Vec4I, 4>> {};

struct OneFourVec4FloatFixture : public ::testing::TestWithParam<FourVec4F>{};

struct OneFourVec4IntFixture : public ::testing::TestWithParam<FourVec4I>{};

struct PairOfFourVec4FloatFixture : public ::testing::TestWithParam<std::pair<FourVec4F, FourVec4F>>{};

struct PairOfFourVec4IntFixture : public ::testing::TestWithParam<std::pair<FourVec4I, FourVec4I>>{};

struct PairOfFourVec4AndScalarFloatFixture : public ::testing::TestWithParam<
        std::pair<FourVec4F, std::array<float, 4>>>{};

struct PairOfFourVec4AndScalarIntFixture : public ::testing::TestWithParam<
        std::pair<FourVec4I, std::array<int, 4>>>{};

INSTANTIATE_TEST_SUITE_P(FourVec4F, ArrayOfFourVec4FloatFixture, testing::Values(
        std::array<Vec4F, 4>{Vec4F(1.f, 2.f, 3.f, 4.f), Vec4F(5.f, 6.f, 7.f, 8.f),
                             Vec4F(9.f, 10.f, 11.f, 12.f), Vec4F(13.f, 14.f, 15.f, 16.f)},
        std::array<Vec4F, 4>{Vec4F(867.43f, 21.005f, 3.00001f, 4.44f),
                             Vec4F(-5.45f, -26.654f, -74.5f, 8.f),
                             Vec4F(-91.f, -10.9999f, 11.f, 12.321f),
                             Vec4F(-13.456f, 14.989f, -15.321f, 16.f)}
));

INSTANTIATE_TEST_SUITE_P(FourVec4I, ArrayOfFourVec4IntFixture, testing::Values(
        std::array<Vec4I, 4>{Vec4I(1, 2, 3, 4), Vec4I(5, 6, 7, 8),
                             Vec4I(9, 10, 11, 12), Vec4I(13, 14, 15, 16)},
        std::array<Vec4I, 4>{Vec4I(-111, 2, -43, 4), Vec4I(-55, 6, 7, -899),
                             Vec4I(9, -10001, 11, -172), Vec4I(-135, 14, -9815, 16)}
));

INSTANTIATE_TEST_SUITE_P(FourVec4F, OneFourVec4FloatFixture, testing::Values(
        FourVec4F(std::array<Vec4F, 4>{
                Vec4F(0.f, 1.f, 0.f, 0.f),
                Vec4F(0.f, 0.f, 5.f, 0.f),
                Vec4F(85.f, 0.f, 0.f, 0.f),
                Vec4F(0.f, 0.f, 0.f, 10.f)}),
        FourVec4F(std::array<Vec4F, 4>{
                Vec4F(1.f, 2.f, 3.f, 4.f),
                Vec4F(5.f, 6.f, 7.f, 8.f),
                Vec4F(9.f, 10.f, 11.f, 12.f),
                Vec4F(13.f, 14.f, 15.f, 16.f)}),
        FourVec4F(std::array<Vec4F, 4>{
                Vec4F(-11.f, -22.f, -33.f, -44.f),
                Vec4F(-55.f, -66.f, -77.f, -88.f),
                Vec4F(-99.f, -100.f, -111.f, -122.f),
                Vec4F(-133.f, -144.f, -155.f, -166.f)})
        ));

INSTANTIATE_TEST_SUITE_P(FourVec4I, OneFourVec4IntFixture, testing::Values(
        FourVec4I(std::array<Vec4I, 4>{
                Vec4I(0, 0, 2, 0),
                Vec4I(0, 5, 0, 0),
                Vec4I(0, 0, 0, 9),
                Vec4I(10, 0, 0, 0)}),
        FourVec4I(std::array<Vec4I, 4>{
                Vec4I(1, 2, 3, 4),
                Vec4I(5, 6, 7, 8),
                Vec4I(9, 10, 11, 12),
                Vec4I(13, 14, 15, 16)}),
        FourVec4I(std::array<Vec4I, 4>{
                Vec4I(-11, -22, -33, -44),
                Vec4I(-55, -66, -77, -88),
                Vec4I(-99, -100, -111, -122),
                Vec4I(-133, -144, -155, -166)})
));

INSTANTIATE_TEST_SUITE_P(FourVec4F, PairOfFourVec4FloatFixture, testing::Values(
        std::pair{FourVec4F(std::array<Vec4F, 4>{
                Vec4F(1.f, 2.f, 3.f, 4.f),
                Vec4F(5.f, 6.f, 7.f, 8.f),
                Vec4F(9.f, 10.f, 11.f, 12.f),
                Vec4F(13.f, 14.f, 15.f, 16.f)}),
                  FourVec4F(std::array<Vec4F, 4>{
                          Vec4F(10.f, 11.f, 12.f, 13.f),
                          Vec4F(14.f, 15.f, 16.f, 17.f),
                          Vec4F(18.f, 19.f, 20.f, 21.f),
                          Vec4F(22.f, 23.f, 24.f, 25.f)})}
));

INSTANTIATE_TEST_SUITE_P(FourVec4I, PairOfFourVec4IntFixture, testing::Values(
        std::pair{FourVec4I(std::array<Vec4I, 4>{
                Vec4I(1, 2, 3, 4),
                Vec4I(5, 6, 7, 8),
                Vec4I(9, 10, 11, 12),
                Vec4I(13, 14, 15, 16)}),
                  FourVec4I(std::array<Vec4I, 4>{
                          Vec4I(10, 11, 12, 13),
                          Vec4I(14, 15, 16, 17),
                          Vec4I(18, 19, 20, 21),
                          Vec4I(22, 23, 24, 25)})}
));

INSTANTIATE_TEST_SUITE_P(FourVec4F, PairOfFourVec4AndScalarFloatFixture, testing::Values(
        std::pair{FourVec4F(std::array<Vec4F, 4>{
                Vec4F(1.f, 2.f, 3.f, 4.f),
                Vec4F(5.f, 6.f, 7.f, 8.f),
                Vec4F(9.f, 10.f, 11.f, 12.f),
                Vec4F(13.f, 14.f, 15.f, 16.f)}),
                  std::array<float, 4>{1.1111f, 5.0000001f, 10.45612f, -500.f}},
        std::pair{FourVec4F(std::array<Vec4F, 4>{
                Vec4F(1.f, 2.f, 3.f, 4.f),
                Vec4F(5.f, 6.f, 7.f, 8.f),
                Vec4F(9.f, 10.f, 11.f, 12.f),
                Vec4F(13.f, 14.f, 15.f, 16.f)}),
                  std::array<float, 4>{0.f, 10.f, 90.000000f, -40.000f}}
));

INSTANTIATE_TEST_SUITE_P(FourVec4I, PairOfFourVec4AndScalarIntFixture, testing::Values(
        std::pair{FourVec4I(std::array<Vec4I, 4>{
                Vec4I(1, 2, 3, 4),
                Vec4I(5, 6, 7, 8),
                Vec4I(9, 10, 11, 12),
                Vec4I(13, 14, 15, 16)}),
                  std::array<int, 4>{1, 5, 10, -500}},
        std::pair{FourVec4I(std::array<Vec4I, 4>{
                Vec4I(1, 2, 3, 4),
                Vec4I(5, 6, 7, 8),
                Vec4I(9, 10, 11, 12),
                Vec4I(13, 14, 15, 16)}),
                  std::array<int, 4>{0, 10, 90, -40}}
));

#pragma endregion FourVec4

#pragma region FourVec4 Tests

TEST_P(ArrayOfFourVec4FloatFixture, Constructor)
{
    auto vecs = GetParam();

    FourVec4F fourV(vecs);

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(fourV.X()[i], vecs[i].X);
        EXPECT_FLOAT_EQ(fourV.Y()[i], vecs[i].Y);
        EXPECT_FLOAT_EQ(fourV.Z()[i], vecs[i].Z);
        EXPECT_FLOAT_EQ(fourV.W()[i], vecs[i].W);
    }
}

TEST_P(ArrayOfFourVec4IntFixture, Constructor)
{
    auto vecs = GetParam();

    FourVec4I fourV(vecs);

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(fourV.X()[i], vecs[i].X);
        EXPECT_EQ(fourV.Y()[i], vecs[i].Y);
        EXPECT_EQ(fourV.Z()[i], vecs[i].Z);
        EXPECT_EQ(fourV.W()[i], vecs[i].W);
    }
}

TEST_P(OneVec4FloatFixture, ConstructorFourVec)
{
    auto v = GetParam();

    FourVec4F fourV(v);

    for (int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(fourV.X()[i], v.X);
        EXPECT_FLOAT_EQ(fourV.Y()[i], v.Y);
        EXPECT_FLOAT_EQ(fourV.Z()[i], v.Z);
        EXPECT_FLOAT_EQ(fourV.W()[i], v.W);
    }
}

TEST_P(OneVec4IntFixture, ConstructorFourVec)
{
    auto v = GetParam();

    FourVec4I fourV(v);

    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(fourV.X()[i], v.X);
        EXPECT_EQ(fourV.Y()[i], v.Y);
        EXPECT_EQ(fourV.Z()[i], v.Z);
        EXPECT_EQ(fourV.W()[i], v.W);
    }
}

TEST_P(PairOfFourVec4FloatFixture, Add)
{
    auto [nV1, nV2] = GetParam();

    auto nVecResult = nV1 + nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual += nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(nVecResult.X()[i], nV1.X()[i] + nV2.X()[i]);
        EXPECT_FLOAT_EQ(nVecResult.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
        EXPECT_FLOAT_EQ(nVecResult.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
        EXPECT_FLOAT_EQ(nVecResult.W()[i], nV1.W()[i] + nV2.W()[i]);

        EXPECT_FLOAT_EQ(nVPlusEqual.X()[i], nV1.X()[i] + nV2.X()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.W()[i], nV1.W()[i] + nV2.W()[i]);
    }
}

TEST_P(PairOfFourVec4IntFixture, Add)
{
    auto [nV1, nV2] = GetParam();

    auto nVecResult = nV1 + nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual += nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nVecResult.X()[i], nV1.X()[i] + nV2.X()[i]);
        EXPECT_EQ(nVecResult.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
        EXPECT_EQ(nVecResult.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
        EXPECT_EQ(nVecResult.W()[i], nV1.W()[i] + nV2.W()[i]);

        EXPECT_EQ(nVPlusEqual.X()[i], nV1.X()[i] + nV2.X()[i]);
        EXPECT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
        EXPECT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
        EXPECT_EQ(nVPlusEqual.W()[i], nV1.W()[i] + nV2.W()[i]);
    }
}

TEST_P(PairOfFourVec4FloatFixture, Sub)
{
    auto [nV1, nV2] = GetParam();

    auto nVecResult = nV1 - nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual -= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(nVecResult.X()[i], nV1.X()[i] - nV2.X()[i]);
        EXPECT_FLOAT_EQ(nVecResult.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
        EXPECT_FLOAT_EQ(nVecResult.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
        EXPECT_FLOAT_EQ(nVecResult.W()[i], nV1.W()[i] - nV2.W()[i]);

        EXPECT_FLOAT_EQ(nVPlusEqual.X()[i], nV1.X()[i] - nV2.X()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.W()[i], nV1.W()[i] - nV2.W()[i]);
    }
}

TEST_P(PairOfFourVec4IntFixture, Sub)
{
    auto [nV1, nV2] = GetParam();

    auto nVecResult = nV1 - nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual -= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nVecResult.X()[i], nV1.X()[i] - nV2.X()[i]);
        EXPECT_EQ(nVecResult.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
        EXPECT_EQ(nVecResult.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
        EXPECT_EQ(nVecResult.W()[i], nV1.W()[i] - nV2.W()[i]);

        EXPECT_EQ(nVPlusEqual.X()[i], nV1.X()[i] - nV2.X()[i]);
        EXPECT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
        EXPECT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
        EXPECT_EQ(nVPlusEqual.W()[i], nV1.W()[i] - nV2.W()[i]);
    }
}

TEST_P(OneFourVec4FloatFixture, MinusOperator)
{
    auto nV = GetParam();

    auto nResult = -nV;

    for (int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(nResult.X()[i], -nV.X()[i]);
        EXPECT_FLOAT_EQ(nResult.Y()[i], -nV.Y()[i]);
        EXPECT_FLOAT_EQ(nResult.Z()[i], -nV.Z()[i]);
        EXPECT_FLOAT_EQ(nResult.W()[i], -nV.W()[i]);
    }
}

TEST_P(OneFourVec4IntFixture, MinusOperator)
{
    auto nV = GetParam();

    auto nResult = -nV;

    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nResult.X()[i], -nV.X()[i]);
        EXPECT_EQ(nResult.Y()[i], -nV.Y()[i]);
        EXPECT_EQ(nResult.Z()[i], -nV.Z()[i]);
        EXPECT_EQ(nResult.W()[i], -nV.W()[i]);
    }
}

TEST_P(PairOfFourVec4FloatFixture, Multiply)
{
    auto [nV1, nV2] = GetParam();

    auto nVecResult = nV1 * nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual *= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(nVecResult.X()[i], nV1.X()[i] * nV2.X()[i]);
        EXPECT_FLOAT_EQ(nVecResult.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
        EXPECT_FLOAT_EQ(nVecResult.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
        EXPECT_FLOAT_EQ(nVecResult.W()[i], nV1.W()[i] * nV2.W()[i]);

        EXPECT_FLOAT_EQ(nVPlusEqual.X()[i], nV1.X()[i] * nV2.X()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.W()[i], nV1.W()[i] * nV2.W()[i]);
    }
}

TEST_P(PairOfFourVec4IntFixture, Multiply)
{
    auto [nV1, nV2] = GetParam();

    auto nVecResult = nV1 * nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual *= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nVecResult.X()[i], nV1.X()[i] * nV2.X()[i]);
        EXPECT_EQ(nVecResult.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
        EXPECT_EQ(nVecResult.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
        EXPECT_EQ(nVecResult.W()[i], nV1.W()[i] * nV2.W()[i]);

        EXPECT_EQ(nVPlusEqual.X()[i], nV1.X()[i] * nV2.X()[i]);
        EXPECT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
        EXPECT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
        EXPECT_EQ(nVPlusEqual.W()[i], nV1.W()[i] * nV2.W()[i]);
    }
}

TEST_P(PairOfFourVec4FloatFixture, Division)
{
    auto [nV1, nV2] = GetParam();

    for (int i = 0; i < 4; i++)
    {
        if (nV2.X()[i] == 0 || nV2.Y()[i] == 0 || nV2.Z()[i] == 0 || nV2.W()[i] == 0)
        {
			FourVec4F result;
            EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
            EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
            return;
        }
    }

    auto nVecResult = nV1 / nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual /= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(nVecResult.X()[i], nV1.X()[i] / nV2.X()[i]);
        EXPECT_FLOAT_EQ(nVecResult.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
        EXPECT_FLOAT_EQ(nVecResult.Z()[i], nV1.Z()[i] / nV2.Z()[i]);
        EXPECT_FLOAT_EQ(nVecResult.W()[i], nV1.W()[i] / nV2.W()[i]);

        EXPECT_FLOAT_EQ(nVPlusEqual.X()[i], nV1.X()[i] / nV2.X()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] / nV2.Z()[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.W()[i], nV1.W()[i] / nV2.W()[i]);
    }
}

TEST_P(PairOfFourVec4IntFixture, Division)
{
    auto [nV1, nV2] = GetParam();

    for (int i = 0; i < 4; i++)
    {
        if (nV2.X()[i] == 0 || nV2.Y()[i] == 0 || nV2.Z()[i] == 0 || nV2.W()[i] == 0)
        {
			FourVec4I result;
            EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
            EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
            return;
        }
    }

    auto nVecResult = nV1 / nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual /= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nVecResult.X()[i], nV1.X()[i] / nV2.X()[i]);
        EXPECT_EQ(nVecResult.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
        EXPECT_EQ(nVecResult.Z()[i], nV1.Z()[i] / nV2.Z()[i]);
        EXPECT_EQ(nVecResult.W()[i], nV1.W()[i] / nV2.W()[i]);

        EXPECT_EQ(nVPlusEqual.X()[i], nV1.X()[i] / nV2.X()[i]);
        EXPECT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
        EXPECT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] / nV2.Z()[i]);
        EXPECT_EQ(nVPlusEqual.W()[i], nV1.W()[i] / nV2.W()[i]);
    }
}

TEST_P(PairOfFourVec4AndScalarFloatFixture, Multiply)
{
    auto [nV1, nV2] = GetParam();

    auto nVecResult = nV1 * nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual *= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(nVecResult.X()[i], nV1.X()[i] * nV2[i]);
        EXPECT_FLOAT_EQ(nVecResult.Y()[i], nV1.Y()[i] * nV2[i]);
        EXPECT_FLOAT_EQ(nVecResult.Z()[i], nV1.Z()[i] * nV2[i]);
        EXPECT_FLOAT_EQ(nVecResult.W()[i], nV1.W()[i] * nV2[i]);

        EXPECT_FLOAT_EQ(nVPlusEqual.X()[i], nV1.X()[i] * nV2[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] * nV2[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] * nV2[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.W()[i], nV1.W()[i] * nV2[i]);
    }
}

TEST_P(PairOfFourVec4AndScalarIntFixture, Multiply)
{
    auto [nV1, nV2] = GetParam();

    auto nVecResult = nV1 * nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual *= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nVecResult.X()[i], nV1.X()[i] * nV2[i]);
        EXPECT_EQ(nVecResult.Y()[i], nV1.Y()[i] * nV2[i]);
        EXPECT_EQ(nVecResult.Z()[i], nV1.Z()[i] * nV2[i]);
        EXPECT_EQ(nVecResult.W()[i], nV1.W()[i] * nV2[i]);

        EXPECT_EQ(nVPlusEqual.X()[i], nV1.X()[i] * nV2[i]);
        EXPECT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] * nV2[i]);
        EXPECT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] * nV2[i]);
        EXPECT_EQ(nVPlusEqual.W()[i], nV1.W()[i] * nV2[i]);
    }
}

TEST_P(PairOfFourVec4AndScalarFloatFixture, Division)
{
    auto [nV1, nV2] = GetParam();

    for (int i = 0; i < 4; i++)
    {
        if (nV2[i] == 0 || nV2[i] == 0 || nV2[i] == 0 || nV2[i] == 0)
        {
			FourVec4F result;
            EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
            EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
            return;
        }
    }

    auto nVecResult = nV1 / nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual /= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(nVecResult.X()[i], nV1.X()[i] / nV2[i]);
        EXPECT_FLOAT_EQ(nVecResult.Y()[i], nV1.Y()[i] / nV2[i]);
        EXPECT_FLOAT_EQ(nVecResult.Z()[i], nV1.Z()[i] / nV2[i]);
        EXPECT_FLOAT_EQ(nVecResult.W()[i], nV1.W()[i] / nV2[i]);

        EXPECT_FLOAT_EQ(nVPlusEqual.X()[i], nV1.X()[i] / nV2[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] / nV2[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] / nV2[i]);
        EXPECT_FLOAT_EQ(nVPlusEqual.W()[i], nV1.W()[i] / nV2[i]);
    }
}

TEST_P(PairOfFourVec4AndScalarIntFixture, Division)
{
    auto [nV1, nV2] = GetParam();

    for (int i = 0; i < 4; i++)
    {
        if (nV2[i] == 0 || nV2[i] == 0 || nV2[i] == 0 || nV2[i] == 0)
        {
			FourVec4I result;
            EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
            EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
            return;
        }
    }

    auto nVecResult = nV1 / nV2;
    auto nVPlusEqual = nV1;
    nVPlusEqual /= nV2;

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(nVecResult.X()[i], nV1.X()[i] / nV2[i]);
        EXPECT_EQ(nVecResult.Y()[i], nV1.Y()[i] / nV2[i]);
        EXPECT_EQ(nVecResult.Z()[i], nV1.Z()[i] / nV2[i]);
        EXPECT_EQ(nVecResult.W()[i], nV1.W()[i] / nV2[i]);

        EXPECT_EQ(nVPlusEqual.X()[i], nV1.X()[i] / nV2[i]);
        EXPECT_EQ(nVPlusEqual.Y()[i], nV1.Y()[i] / nV2[i]);
        EXPECT_EQ(nVPlusEqual.Z()[i], nV1.Z()[i] / nV2[i]);
        EXPECT_EQ(nVPlusEqual.W()[i], nV1.W()[i] / nV2[i]);
    }
}

TEST_P(PairOfFourVec4FloatFixture, Dot)
{
    auto [nV1, nV2] = GetParam();

    auto dots = FourVec4F::Dot(nV1, nV2);

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(dots[i], nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i] +
                           nV1.Z()[i] * nV2.Z()[i] + nV1.W()[i] * nV2.W()[i]);
    }
}

TEST_P(PairOfFourVec4IntFixture, Dot)
{
    auto [nV1, nV2] = GetParam();

    auto dots = FourVec4I::Dot(nV1, nV2);

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(dots[i], nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i] +
                           nV1.Z()[i] * nV2.Z()[i] + nV1.W()[i] * nV2.W()[i]);
    }
}

TEST_P (OneFourVec4FloatFixture, SquareMagnitude)
{
    auto nV = GetParam();

    auto sM = nV.SquareMagnitude();

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(sM[i], nV.X()[i] * nV.X()[i] + nV.Y()[i] * nV.Y()[i] +
                               nV.Z()[i] * nV.Z()[i] + nV.W()[i] * nV.W()[i]);
    }
}

TEST_P (OneFourVec4IntFixture, SquareMagnitude)
{
    auto nV = GetParam();

    auto sM = nV.SquareMagnitude();

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(sM[i], nV.X()[i] * nV.X()[i] + nV.Y()[i] * nV.Y()[i] +
                               nV.Z()[i] * nV.Z()[i] + nV.W()[i] * nV.W()[i]);
    }
}

TEST_P (OneFourVec4FloatFixture, Magnitude)
{
    auto nV = GetParam();

    auto sM = nV.SquareMagnitude();

    auto m = nV.Magnitude();

    for(int i = 0; i < 4; i++)
    {
        EXPECT_FLOAT_EQ(m[i], std::sqrt(sM[i]));
    }
}

TEST_P (OneFourVec4IntFixture, Magnitude)
{
    auto nV = GetParam();

    auto sM = nV.SquareMagnitude();

    auto m = nV.Magnitude();

    for(int i = 0; i < 4; i++)
    {
        EXPECT_EQ(m[i], static_cast<int>(std::sqrt(sM[i])));
    }
}

TEST_P(OneFourVec4FloatFixture, Normalized)
{
    auto nV = GetParam();

    auto magnitude = nV.Magnitude();

    std::array<float, 4> normalized{};

    for (int i = 0; i < 4; i++)
    {
        if (magnitude[i] == 0)
        {
            EXPECT_THROW(normalized = nV.Normalized(), DivisionByZeroException);
            return;
        }
    }

    normalized = nV.Normalized();
    const auto array1N = nV.SquareMagnitude();
    std::array<float, 4> reciprocalSqrt = std::array<float, 4>();

    constexpr auto epsilon = 0.001f;

    for (int i = 0; i < 4; i++)
    {
        reciprocalSqrt[i] = 1 / std::sqrt(array1N[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        EXPECT_NEAR(normalized[i], reciprocalSqrt[i], epsilon);
    }
}

TEST_P(OneFourVec4IntFixture, Normalized)
{
    auto nV = GetParam();

    auto magnitude = nV.Magnitude();

    std::array<int, 4> normalized{};

    for (int i = 0; i < 4; i++)
    {
        if (magnitude[i] == 0)
        {
            EXPECT_THROW(normalized = nV.Normalized(), DivisionByZeroException);
            return;
        }
    }

    normalized = nV.Normalized();
    const auto array1N = nV.SquareMagnitude();
    std::array<int, 4> reciprocalSqrt = std::array<int, 4>();

    for (int i = 0; i < 4; i++)
    {
        reciprocalSqrt[i] = static_cast<int>(1 / std::sqrt(array1N[i]));
    }

    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(normalized[i], static_cast<int>(reciprocalSqrt[i]));
    }
}

#pragma endregion FourVec4 Tests