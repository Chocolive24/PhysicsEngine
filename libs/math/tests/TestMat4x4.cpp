/**
 * @author Olivier, Alexis, Rémy, Constantin
 */

#include "Mat4x4.h"
#include "Utility.h"

#include "gtest/gtest.h"

#include <array>

using namespace Math;

struct MatrixConstructorParamFixture : public ::testing::TestWithParam<std::array<Vec4I, Mat4x4I::RowNbr>>
{
};

struct MatrixIntOperationFixture : public ::testing::TestWithParam<std::pair<Mat4x4I, Mat4x4I>>
{
};

struct MatrixAndScalarIntOperationFixture : public ::testing::TestWithParam<std::pair<Mat4x4I, int>>
{
};

struct MatrixAndVectorIntOperationFixture : public ::testing::TestWithParam<std::pair<Mat4x4I, Vec4I>>
{
};

struct MatrixIntFixture : public ::testing::TestWithParam<Mat4x4I>
{
};

struct MatrixFloatFixture : public ::testing::TestWithParam<Mat4x4F>
{
};

INSTANTIATE_TEST_SUITE_P(Mat4x4I, MatrixConstructorParamFixture, testing::Values(
        std::array<Vec4I, Mat4x4I::RowNbr>{Vec4I(1, 2, 3, 4), Vec4I(5, 6, 7, 8),
                             Vec4I(9, 10, 11, 12), Vec4I(13, 14, 15, 16)},
        std::array<Vec4I, Mat4x4I::RowNbr>{Vec4I(-11, -42, -13, -1), Vec4I(4, -35, 6, -5),
                             Vec4I(-47, -8, -9, 43), Vec4I(-1, -4, -8, 15)}
));

INSTANTIATE_TEST_SUITE_P(Mat4x4I, MatrixIntOperationFixture, testing::Values(
        std::pair{
                Mat4x4I(Vec4I(1, 2, 3, 4), Vec4I(5, 6, 7, 8),
                        Vec4I(9, 10, 11, 12), Vec4I(13, 14, 15, 16)),
                Mat4x4I(Vec4I(2, 3, 4, 18), Vec4I(5, 6, 7, 15),
                        Vec4I(8, 9, 10, 56), Vec4I(8, 9, 10, 5))},
        std::pair{
                Mat4x4I(Vec4I(-5, -2, -3, -1), Vec4I(-56, -5, -86, -5),
                        Vec4I(-7, -8, -9, -3), Vec4I(8, -9, -10, 56)),
                Mat4x4I(Vec4I(-560, -3, -4, 12), Vec4I(-35, -56, -7, 4),
                        Vec4I(-8, -9, 54, 9), Vec4I(8, 4, -10, 3))}
));

INSTANTIATE_TEST_SUITE_P(Mat4x4I, MatrixAndScalarIntOperationFixture, testing::Values(
        std::pair{Mat4x4I(Vec4I(1, 2, 3, 4), Vec4I(5, 6, 7, 8),
                   Vec4I(9, 10, 11, 12), Vec4I(13, 14, 15, 16)),
                  2},
        std::pair{Mat4x4I(Vec4I(-10, 24, -3, -1), Vec4I(-4, 45, -26, 23),
                Vec4I(7, -8, 9,3), Vec4I(-8, -54, 3, -9)),
                  -52}
));

INSTANTIATE_TEST_SUITE_P(Mat4x4I_Vec4I, MatrixAndVectorIntOperationFixture, testing::Values(
        std::pair{Mat4x4I(Vec4I(1, 2, 3, 4), Vec4I(5, 6, 7, 8),
                          Vec4I(9, 10, 11, 12), Vec4I(13, 14, 15, 16)),
                  Vec4I(23, 10, 2, 32)},
        std::pair{Mat4x4I(Vec4I(-10, 24, -3, -1), Vec4I(-4, 45, -26, 23),
                          Vec4I(7, -8, 9,3), Vec4I(-8, -54, 3, -9)),
                  Vec4I(-14, 100, -23, -15)}
));

INSTANTIATE_TEST_SUITE_P(Mat4x4I, MatrixIntFixture, testing::Values(
        Mat4x4I(Vec4I(1, 2, 3, 4), Vec4I(5, 6, 7, 8),
                Vec4I(9, 10, 11, 12), Vec4I(13, 14, 15, 16)),
        Mat4x4I(Vec4I(0, 0, 0, 0), Vec4I(0, 0, 0, 0),
                Vec4I(0, 0, 0, 0), Vec4I(0, 0, 0, 0)),
        Mat4x4I(Vec4I(-20, -2, -9, -2), Vec4I(-10, -34, -3, -15),
                Vec4I(2, -40, -21, -32), Vec4I(-4, 2, 3, 10))
));

INSTANTIATE_TEST_SUITE_P(Mat4x4F, MatrixFloatFixture, testing::Values(
        Mat4x4F(Vec4F(1.f, 2.f, 3.f, 4.f), Vec4F(5.f, 6.f, 7.f, 8.f),
                Vec4F(9.f, 10.f, 11.f, 12.f), Vec4F(13.f, 14.f, 15.f, 16.f)),
        Mat4x4F(Vec4F(0.f, 0.f, 0.f, 0.f), Vec4F(0.f, 0.f, 0.f, 0.f),
                Vec4F(0.f, 0.f, 0.f, 0.f), Vec4F(0.f, 0.f, 0.f, 0.f)),
        Mat4x4F(Vec4F(-20.32f, -2.0098f, -93.f, -4.2317f), Vec4F(-10.34f, -34.43f, -3.f, -54.32f),
                Vec4F(2.22f, -40.9856f, -21.23f, 1.11111f), Vec4F(7.654321f, 1.1f, 2.45f, 9.f))
));

TEST(Constructors, Default)
{
    Mat4x4I m;

    int expectedValues[Mat4x4I::RowNbr][Mat4x4I::ColNbr]
            {{1, 0, 0, 0}, {0, 1, 0, 0},
             {0, 0, 1, 0}, {0, 0, 0, 1}};

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        for (int col = 0; col < Mat4x4I::ColNbr; col++)
        {
            EXPECT_EQ(m.Val[row][col], expectedValues[row][col]);
        }
    }
}

TEST_P(MatrixConstructorParamFixture, ConstructorWithVec4I)
{
    auto vectors = GetParam();

    Mat4x4I m(vectors[0], vectors[1], vectors[2], vectors[3]);

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        EXPECT_EQ(m.Val[row][0], vectors[0][row]);
        EXPECT_EQ(m.Val[row][1], vectors[1][row]);
        EXPECT_EQ(m.Val[row][2], vectors[2][row]);
        EXPECT_EQ(m.Val[row][3], vectors[3][row]);
    }
}

TEST(ConstexprFunctions, Identity)
{
    Mat4x4I m = Mat4x4I::Identity();

    int expectedValues[Mat4x4I::RowNbr][Mat4x4I::ColNbr]
            {{1, 0, 0, 0}, {0, 1, 0, 0},
             {0, 0, 1, 0}, {0, 0, 0, 1}};

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        for (int col = 0; col < Mat4x4I::ColNbr; col++)
        {
            EXPECT_EQ(m.Val[row][col], expectedValues[row][col]);
        }
    }
}

TEST_P(MatrixIntOperationFixture, Add)
{
    auto [m1, m2] = GetParam();

    Mat4x4I m1PlusM2 = m1 + m2;
    Mat4x4I m1PlusEqualM2 = m1;
    m1PlusEqualM2 += m2;

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        for (int col = 0; col < Mat4x4I::ColNbr; col++)
        {
            EXPECT_EQ(m1PlusM2.Val[row][col], m1.Val[row][col] + m2.Val[row][col]);
            EXPECT_EQ(m1PlusEqualM2.Val[row][col], m1.Val[row][col] + m2.Val[row][col]);
        }
    }
}

TEST_P(MatrixIntOperationFixture, Sub)
{
    auto [m1, m2] = GetParam();

    Mat4x4I m1MinusM2 = m1 - m2;
    Mat4x4I m1MinusEqualM2 = m1;
    m1MinusEqualM2 -= m2;

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        for (int col = 0; col < Mat4x4I::ColNbr; col++)
        {
            EXPECT_EQ(m1MinusM2.Val[row][col], m1.Val[row][col] - m2.Val[row][col]);
            EXPECT_EQ(m1MinusEqualM2.Val[row][col], m1.Val[row][col] - m2.Val[row][col]);
        }
    }
}

TEST_P(MatrixAndScalarIntOperationFixture, MultiplyByScalar)
{
    auto [m, scalar] = GetParam();

    Mat4x4I mTimeScalar = m * scalar;
    Mat4x4I scalarTimeM = scalar * m;
    Mat4x4I mTimeEqualScalar = m;
    mTimeEqualScalar *= scalar;

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        for (int col = 0; col < Mat4x4I::ColNbr; col++)
        {
            EXPECT_EQ(mTimeScalar.Val[row][col], m.Val[row][col] * scalar);
            EXPECT_EQ(scalarTimeM.Val[row][col], m.Val[row][col] * scalar);
            EXPECT_EQ(mTimeEqualScalar.Val[row][col], m.Val[row][col] * scalar);
        }
    }
}

TEST_P(MatrixIntOperationFixture, MultiplyByMatrix)
{
    auto [m1, m2] = GetParam();

    Mat4x4I m1m2 = m1 * m2;
    Mat4x4I m1TimeEqualM2 = m1;
    m1TimeEqualM2 *= m2;

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        for (int col = 0; col < Mat4x4I::ColNbr; col++)
        {
            int sum = 0;

            for (int k = 0; k < 4; k++)
            {
                sum += m1.Val[row][k] * m2.Val[k][col];
            }

            EXPECT_EQ(m1m2.Val[row][col], sum);
            EXPECT_EQ(m1TimeEqualM2.Val[row][col], sum);
        }
    }
}

TEST_P(MatrixAndVectorIntOperationFixture, MultiplyWithVec)
{
    auto [m, v] = GetParam();

    Vec4I result = m * v;

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        int internResult = 0;
        for (int j = 0; j < Mat4x4I::RowNbr; j++)
        {
            internResult += m.Val[row][j] * v[j];
        }

        EXPECT_EQ(result[row], internResult);
    }
}

TEST_P(MatrixIntFixture, Cast)
{
    auto m = GetParam();

    auto mFloat = static_cast<Mat4x4F>(m);
    auto mDouble = static_cast<Mat4x4<double>>(m);
    auto mLongLongInt = static_cast<Mat4x4<long long int>>(m);

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        for (int col = 0; col < Mat4x4I::ColNbr; col++)
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

    int det = 0;

    for (std::size_t col = 0; col < Mat4x4I::ColNbr; col++) {
        int sign = (1 + (col + 1)) % 2 == 0 ? 1 : -1;

        Mat3x3<int> subMat;
        std::size_t subMatRow = 0, subMatCol = 0;

        for (std::size_t subRow = 0; subRow < Mat4x4I::RowNbr; subRow++) {
            if (subRow == 0) continue;

            for (std::size_t subCol = 0; subCol < Mat4x4I::ColNbr; subCol++) {
                if (subCol == col) continue;

                // Add the value to the sub-matrix.
                subMat.Val[subMatRow][subMatCol] = m.Val[subRow][subCol];
                subMatCol++;
            }

            subMatRow++;
            subMatCol = 0;
        }

        // Det(A) = sum of all : (-1)^1+i * a1i * det(A1i)
        det += sign * m.Val[0][col] * subMat.Det();
    }

    EXPECT_EQ(m.Det(), det);
}

TEST_P(MatrixIntFixture, Transposition)
{
    auto m = GetParam();

    Mat4x4I mTrans = m.Transposed();
    Mat4x4I mCopy = m;
    m.Transpose();

    for (int row = 0; row < Mat4x4I::RowNbr; row++)
    {
        for (int col = 0; col < Mat4x4I::ColNbr; col++)
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

    Mat4x4F inverted;

    if (det == 0)
    {
        EXPECT_THROW(inverted = m.Inverted<float>(), DivisionByZeroException);
        EXPECT_THROW(m.Invert<float>(), DivisionByZeroException);
        return;
    }

    Mat4x4F identity = Mat4x4F::Identity();
    Mat4x4F mCopy = m;
    inverted = m.Inverted<float>();
    m.Invert<float>();

    Mat4x4F isInvertedCorrect = mCopy * inverted;
    Mat4x4F isMInverted = mCopy * m;

    for (int row = 0; row < Mat3x3I::RowNbr; row++)
    {
        for (int col = 0; col < Mat3x3I::ColNbr; col++)
        {
            EXPECT_NEAR(isInvertedCorrect.Val[row][col], identity.Val[row][col], Epsilon);
            EXPECT_NEAR(isMInverted.Val[row][col], identity.Val[row][col], Epsilon);
        }
    }
}