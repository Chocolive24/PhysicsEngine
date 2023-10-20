/**
 * @author Olivier
 */

#include <array>
#include "gtest/gtest.h"
#include "Mat3x3.h"
#include "Utility.h"

using namespace Math;

struct MatrixConstructorParamFixture : public ::testing::TestWithParam<std::array<Vec3I, 3>> {};

struct MatrixIntOperationFixture : public ::testing::TestWithParam<std::pair<Mat3x3I, Mat3x3I>> {};

struct MatrixAndScalarIntOperationFixture : public ::testing::TestWithParam<std::pair<Mat3x3I, int>> {};

struct MatrixAndVectorIntOperationFixture : public ::testing::TestWithParam<std::pair<Mat3x3I, Vec3I>> {};

struct MatrixIntFixture : public ::testing::TestWithParam<Mat3x3I> {};

struct MatrixFloatFixture : public ::testing::TestWithParam<Mat3x3F> {};

INSTANTIATE_TEST_SUITE_P(Mat3x3I, MatrixConstructorParamFixture, testing::Values(
        std::array<Vec3I, 3>{Vec3I(1, 2, 3), Vec3I(4, 5, 6), Vec3I(7, 8, 9)},
        std::array<Vec3I, 3>{Vec3I(-11, -42, -13), Vec3I(4, -35, 6), Vec3I(-47, -8, -9)}
));

INSTANTIATE_TEST_SUITE_P(Mat3x3I, MatrixIntOperationFixture, testing::Values(
        std::pair{
                Mat3x3I(Vec3I(1, 2, 3), Vec3I(4, 5, 6), Vec3I(7, 8, 9)),
                Mat3x3I(Vec3I(2, 3, 4), Vec3I(5, 6, 7), Vec3I(8, 9, 10))},
        std::pair{
                Mat3x3I(Vec3I(-5, -2, -3), Vec3I(-56, -5, -86),
                        Vec3I(-7, -8, -9)),
                Mat3x3I(Vec3I(-560, -3, -4), Vec3I(-35, -56, -7),
                        Vec3I(-8, -9, 54))}
));

INSTANTIATE_TEST_SUITE_P(Mat3x3I, MatrixAndScalarIntOperationFixture, testing::Values(
        std::pair{Mat3x3I(
                Vec3I(1, 2, 3), Vec3I(4, 5, 6), Vec3I(7, 8, 9)),
                  2},
        std::pair{Mat3x3I(
                Vec3I(-10, 24, -3), Vec3I(-4, 45, -26), Vec3I(7, -8, 9)),
                  -52}
));

INSTANTIATE_TEST_SUITE_P(Mat3x3I_Vec3I, MatrixAndVectorIntOperationFixture, testing::Values(
        std::pair{Mat3x3I(
                Vec3I(1, 2, 3), Vec3I(4, 5, 6), Vec3I(7, 8, 9)),
                  Vec3I(23, 10, 2)},
        std::pair{Mat3x3I(
                Vec3I(-10, 24, -3), Vec3I(-4, 45, -26), Vec3I(7, -8, 9)),
                  Vec3I(-14, 100, -23)}
));

INSTANTIATE_TEST_SUITE_P(Mat3x3I, MatrixIntFixture, testing::Values(
        Mat3x3I(Vec3I(1, 2, 3), Vec3I(4, 5, 6), Vec3I(7, 8, 9)),
        Mat3x3I(Vec3I(0, 0, 0), Vec3I(0, 0, 0), Vec3I(0, 0, 0)),
        Mat3x3I(Vec3I(-20, -2, -9), Vec3I(-10, -34, -3), Vec3I(2, -40, -21))
));

INSTANTIATE_TEST_SUITE_P(Mat3x3F, MatrixFloatFixture, testing::Values(
        Mat3x3F(Vec3F(1.f, 2.f, 3.f), Vec3F(4.f, 5.f, 6.f), Vec3F(7.f, 8.f, 9.f)),
        Mat3x3F(Vec3F(0.f, 0.f, 0.f), Vec3F(0.f, 0.f, 0.f), Vec3F(0.f, 0.f, 0.f)),
        Mat3x3F(Vec3F(-20.32f, -2.0098f, -93.f), Vec3F(-10.34f, -34.43f, -3.f),
                Vec3F(2.22f, -40.9856f, -21.23f))
));

TEST(Constructors, Default)
{
    Mat3x3I m;

    int expectedValues[Mat3x3I::RowNbr][Mat3x3I::ColNbr]
            {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_EQ(m.Val[row][col], expectedValues[row][col]);
        }
    }
}

TEST_P(MatrixConstructorParamFixture, ConstructorWithVec3I)
{
    auto vectors = GetParam();

    Mat3x3I m(vectors[0], vectors[1], vectors[2]);

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        EXPECT_EQ(m.Val[row][0], vectors[0][row]);
        EXPECT_EQ(m.Val[row][1], vectors[1][row]);
        EXPECT_EQ(m.Val[row][2], vectors[2][row]);
    }
}

TEST(ConstexprFunctions, Identity)
{
    Mat3x3I m = Mat3x3I::Identity();

    int expectedValues[Mat3x3I::RowNbr][Mat3x3I::ColNbr]
            {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_EQ(m.Val[row][col], expectedValues[row][col]);
        }
    }
}

TEST_P(MatrixIntOperationFixture, Add)
{
    auto [m1, m2] = GetParam();

    Mat3x3I m1PlusM2 = m1 + m2;
    Mat3x3I m1PlusEqualM2 = m1;
    m1PlusEqualM2 += m2;

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_EQ(m1PlusM2.Val[row][col], m1.Val[row][col] + m2.Val[row][col]);
            EXPECT_EQ(m1PlusEqualM2.Val[row][col], m1.Val[row][col] + m2.Val[row][col]);
        }
    }
}

TEST_P(MatrixIntOperationFixture, Sub)
{
    auto [m1, m2] = GetParam();

    Mat3x3I m1MinusM2 = m1 - m2;
    Mat3x3I m1MinusEqualM2 = m1;
    m1MinusEqualM2 -= m2;

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_EQ(m1MinusM2.Val[row][col], m1.Val[row][col] - m2.Val[row][col]);
            EXPECT_EQ(m1MinusEqualM2.Val[row][col], m1.Val[row][col] - m2.Val[row][col]);
        }
    }
}

TEST_P(MatrixIntOperationFixture, Multiply)
{
    auto [m1, m2] = GetParam();

    Mat3x3I m1m2 = m1 * m2;
    Mat3x3I m1TimeEqualM2 = m1;
    m1TimeEqualM2 *= m2;

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            int sum = 0;

            for (int k = 0; k < 3; k++)
            {
                sum += m1.Val[row][k] * m2.Val[k][col];
            }

            EXPECT_EQ(m1m2.Val[row][col], sum);
            EXPECT_EQ(m1TimeEqualM2.Val[row][col], sum);
        }
    }
}

TEST_P(MatrixAndScalarIntOperationFixture, Multiply)
{
    auto [m, scalar] = GetParam();

    Mat3x3I mTimeScalar = m * scalar;
    Mat3x3I scalarTimeM = scalar * m;
    Mat3x3I mTimeEqualScalar = m;
    mTimeEqualScalar *= scalar;

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_EQ(mTimeScalar.Val[row][col], m.Val[row][col] * scalar);
            EXPECT_EQ(scalarTimeM.Val[row][col], scalar * m.Val[row][col]);
            EXPECT_EQ(mTimeEqualScalar.Val[row][col], m.Val[row][col] * scalar);
        }
    }
}

TEST_P(MatrixAndVectorIntOperationFixture, Multiply)
{
    auto [m, v] = GetParam();

    Vec3I result = m * v;

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        int internResult = 0;
        for (int j = 0; j < Mat3x3I::RowNbr; j++)
        {
            internResult += m.Val[row][j] * v[j];
        }

        EXPECT_EQ(result[row], internResult);
    }
}

TEST_P(MatrixIntFixture, Cast)
{
    auto m = GetParam();

    auto mFloat = static_cast<Mat3x3F>(m);
    auto mDouble = static_cast<Mat3x3<double>>(m);
    auto mLongLongInt = static_cast<Mat3x3<long long int>>(m);

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_FLOAT_EQ(mFloat.Val[row][col], static_cast<float>(m.Val[row][col]));
            EXPECT_DOUBLE_EQ(mDouble.Val[row][col], static_cast<double>(m.Val[row][col]));
            EXPECT_EQ(mLongLongInt.Val[row][col], static_cast<long long int>(m.Val[row][col]));
        }
    }
}

TEST_P(MatrixIntFixture, Determinant)
{
    auto m = GetParam();

    int det = m.Val[0][0] * m.Val[1][1] * m.Val[2][2] + m.Val[0][1] * m.Val[1][2] * m.Val[2][0]
              + m.Val[0][2] * m.Val[1][0] * m.Val[2][1] - m.Val[2][0] * m.Val[1][1] * m.Val[0][2]
              - m.Val[2][1] * m.Val[1][2] * m.Val[0][0] - m.Val[2][2] * m.Val[1][0] * m.Val[0][1];

    EXPECT_EQ(m.Det(), det);
}

TEST_P(MatrixIntFixture, Transposition)
{
    auto m = GetParam();

    Mat3x3I mTrans = m.Transposed();
    Mat3x3I mCopy = m;
    m.Transpose();

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_EQ(mTrans.Val[row][col], mCopy.Val[col][row]);
            EXPECT_EQ(m.Val[row][col], mCopy.Val[col][row]);
        }
    }
}

TEST_P(MatrixFloatFixture, Inversion)
{
    auto m = GetParam();

    auto det = m.Det();

    Mat3x3F inverted;

    if (det == 0)
    {
        EXPECT_THROW(inverted = m.Inverted<float>(), DivisionByZeroException);
        EXPECT_THROW(m.Invert<float>(), DivisionByZeroException);
        return;
    }

    Mat3x3F identity = Mat3x3F::Identity();
    Mat3x3F mCopy = m;
    inverted = m.Inverted<float>();
    m.Invert<float>();

    Mat3x3F isInvertedCorrect = mCopy * inverted;
    Mat3x3F isMInverted = mCopy * m;

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_NEAR(isInvertedCorrect.Val[row][col], identity.Val[row][col], Epsilon);
            EXPECT_NEAR(isMInverted.Val[row][col], identity.Val[row][col], Epsilon);
        }
    }
}