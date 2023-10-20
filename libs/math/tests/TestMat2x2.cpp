
/**
 * \brief Matrix 2x2 tests for all functions
 * \author Constantin Verine
 */

#include <array>
#include "gtest/gtest.h"
#include "Mat2x2.h"
#include "Utility.h"

using namespace Math;

struct MatrixConstructorIntParamFixture :
        public ::testing::TestWithParam<std::array<Vec2I, 2>>
{
};

struct MatrixConstructorFloatParamFixture :
        public ::testing::TestWithParam<std::array<Vec2F, 2>>
{
};

struct MatrixIntFixture :
        public ::testing::TestWithParam<Mat2x2I>
{
};

struct MatrixFloatFixture :
        public ::testing::TestWithParam<Mat2x2F>
{
};

INSTANTIATE_TEST_SUITE_P(Mat2x2I, MatrixConstructorIntParamFixture, testing::Values(
        std::array<Vec2I, 2>{ Vec2I(1, 2), Vec2I(3, 4) },
        std::array<Vec2I, 2>{ Vec2I(-21, -45), Vec2I(12, -5) },
        std::array<Vec2I, 2>{ Vec2I(0, -0), Vec2I(-0, 0) }
));

INSTANTIATE_TEST_SUITE_P(Mat2x2F, MatrixConstructorFloatParamFixture, testing::Values(
        std::array<Vec2F, 2>{ Vec2F(1.3f, 2.6f), Vec2F(3.5f, 4.7f) },
        std::array<Vec2F, 2>{ Vec2F(-21.2f, -45.3f), Vec2F(12.4f, -5.5f) },
        std::array<Vec2F, 2>{ Vec2F(0.f, -0.f), Vec2F(-0.f, 0.f) }
));

INSTANTIATE_TEST_SUITE_P(Mat2x2I, MatrixIntFixture, testing::Values(
        Mat2x2I(Vec2I(1, 2), Vec2I(3, 4)),
        Mat2x2I(Vec2I(0, 0), Vec2I(0, 0)),
        Mat2x2I(Vec2I(-20, -9), Vec2I(34, -3))
));

INSTANTIATE_TEST_SUITE_P(Mat2x2F, MatrixFloatFixture, testing::Values(
        Mat2x2F(Vec2F(1.2f, 2.3f), Vec2F(3.4f, 4.5)),
        Mat2x2F(Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)),
        Mat2x2F(Vec2F(-20.f, -9.f), Vec2F(34.f, -3.f))
));

TEST (Mat2x2, DefaultConstructor)
{
    const Mat2x2I m;
    constexpr int expectedValues[] = { 1, 0, 0, 1 };

    EXPECT_EQ(m.Val[0][0], expectedValues[0]);
    EXPECT_EQ(m.Val[0][1], expectedValues[1]);
    EXPECT_EQ(m.Val[1][0], expectedValues[2]);
    EXPECT_EQ(m.Val[1][1], expectedValues[3]);
}

TEST (Mat2x2, MatIdentityTest)
{
    const Mat2x2I m = Mat2x2I::Identity();
    constexpr int expectedValues[] = { 1, 0, 0, 1 };

    EXPECT_EQ(m.Val[0][0], expectedValues[0]);
    EXPECT_EQ(m.Val[0][1], expectedValues[1]);
    EXPECT_EQ(m.Val[1][0], expectedValues[2]);
    EXPECT_EQ(m.Val[1][1], expectedValues[3]);
}

TEST_P(MatrixConstructorIntParamFixture, MatConstructorTestInt)
{
    auto vectors = GetParam();
    const Mat2x2I m(vectors[0], vectors[1]);

    EXPECT_EQ(m.Val[0][0], vectors[0][0]);
    EXPECT_EQ(m.Val[0][1], vectors[1][0]);
    EXPECT_EQ(m.Val[1][0], vectors[0][1]);
    EXPECT_EQ(m.Val[1][1], vectors[1][1]);
}

TEST_P(MatrixConstructorFloatParamFixture, MatConstructorTestFloat)
{

    auto vectors = GetParam();
    const Mat2x2F m(vectors[0], vectors[1]);

    EXPECT_EQ(m.Val[0][0], vectors[0][0]);
    EXPECT_EQ(m.Val[0][1], vectors[1][0]);
    EXPECT_EQ(m.Val[1][0], vectors[0][1]);
    EXPECT_EQ(m.Val[1][1], vectors[1][1]);
}

TEST_P(MatrixIntFixture, DetInt)
{
    auto m = GetParam();

    EXPECT_EQ(m.Det(), m.Val[0][0] * m.Val[1][1] - m.Val[0][1] * m.Val[1][0]);
}

TEST_P(MatrixFloatFixture, DetFloat)
{
    auto m = GetParam();

    EXPECT_EQ(m.Det(), m.Val[0][0] * m.Val[1][1] - m.Val[0][1] * m.Val[1][0]);
}

TEST_P(MatrixIntFixture, MatIntTransposeTest)
{
    auto m = GetParam();
    auto mTrans = m.Transposed();

    EXPECT_EQ(mTrans.Val[0][0], m.Val[0][0]);
    EXPECT_EQ(mTrans.Val[0][1], m.Val[1][0]);
    EXPECT_EQ(mTrans.Val[1][0], m.Val[0][1]);
    EXPECT_EQ(mTrans.Val[1][1], m.Val[1][1]);
}

TEST_P(MatrixFloatFixture, MatFloatTransposeTest)
{
    auto m = GetParam();
    auto mTrans = m.Transposed();

    EXPECT_EQ(mTrans.Val[0][0], m.Val[0][0]);
    EXPECT_EQ(mTrans.Val[0][1], m.Val[1][0]);
    EXPECT_EQ(mTrans.Val[1][0], m.Val[0][1]);
    EXPECT_EQ(mTrans.Val[1][1], m.Val[1][1]);
}

TEST_P(MatrixIntFixture, MatIntInvertedTest)
{
    Mat2x2I m = GetParam();
    int det = m.Det();
    Mat2x2F mInv;

    if (det == 0)
    {
        EXPECT_THROW(mInv = m.Inverted<float>(), DivisionByZeroException);
        return;
    }

    mInv = m.Inverted<float>();
    Mat2x2F mId = Mat2x2F::Identity();

    // Check that the inverted matrix is correct
    EXPECT_FLOAT_EQ(mInv.Val[0][0], m.Val[1][1] * 1.f / det);
    EXPECT_FLOAT_EQ(mInv.Val[0][1], m.Val[0][1] * -1.f / det);
    EXPECT_FLOAT_EQ(mInv.Val[1][0], m.Val[1][0] * -1.f / det);
    EXPECT_FLOAT_EQ(mInv.Val[1][1], m.Val[0][0] * 1.f / det);

    mInv *= static_cast<Mat2x2F>(m);

    // Check that the inverted matrix * base matrix = identity matrix
    EXPECT_NEAR(mInv.Val[0][0], mId.Val[0][0], Epsilon);
    EXPECT_NEAR(mInv.Val[0][1], mId.Val[0][1], Epsilon);
    EXPECT_NEAR(mInv.Val[1][0], mId.Val[1][0], Epsilon);
    EXPECT_NEAR(mInv.Val[1][1], mId.Val[1][1], Epsilon);
}

TEST_P(MatrixIntFixture, AdditionInt)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    auto mAdd = m1 + m2;

    EXPECT_EQ(mAdd.Val[0][0], m1.Val[0][0] + m2.Val[0][0]);
    EXPECT_EQ(mAdd.Val[0][1], m1.Val[0][1] + m2.Val[0][1]);
    EXPECT_EQ(mAdd.Val[1][0], m1.Val[1][0] + m2.Val[1][0]);
    EXPECT_EQ(mAdd.Val[1][1], m1.Val[1][1] + m2.Val[1][1]);
}

TEST_P(MatrixFloatFixture, AdditionFloat)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    auto mAdd = m1 + m2;

    EXPECT_EQ(mAdd.Val[0][0], m1.Val[0][0] + m2.Val[0][0]);
    EXPECT_EQ(mAdd.Val[0][1], m1.Val[0][1] + m2.Val[0][1]);
    EXPECT_EQ(mAdd.Val[1][0], m1.Val[1][0] + m2.Val[1][0]);
    EXPECT_EQ(mAdd.Val[1][1], m1.Val[1][1] + m2.Val[1][1]);
}

TEST_P(MatrixIntFixture, MatIntAddEqualTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2I mAdd = m1;

    mAdd += m2;

    // Check that matrix += matrix is correct
    EXPECT_EQ(mAdd.Val[0][0], m1.Val[0][0] + m2.Val[0][0]);
    EXPECT_EQ(mAdd.Val[0][1], m1.Val[0][1] + m2.Val[0][1]);
    EXPECT_EQ(mAdd.Val[1][0], m1.Val[1][0] + m2.Val[1][0]);
    EXPECT_EQ(mAdd.Val[1][1], m1.Val[1][1] + m2.Val[1][1]);
}

TEST_P(MatrixFloatFixture, MatFloatAddEqualTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2F mAdd = m1;

    mAdd += m2;

    // Check that matrix += matrix is correct
    EXPECT_EQ(mAdd.Val[0][0], m1.Val[0][0] + m2.Val[0][0]);
    EXPECT_EQ(mAdd.Val[0][1], m1.Val[0][1] + m2.Val[0][1]);
    EXPECT_EQ(mAdd.Val[1][0], m1.Val[1][0] + m2.Val[1][0]);
    EXPECT_EQ(mAdd.Val[1][1], m1.Val[1][1] + m2.Val[1][1]);
}

TEST_P(MatrixIntFixture, MatIntSubTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2I mSub = m1 - m2;

    // Check that substraction of 2 matrices is correct
    EXPECT_EQ(mSub.Val[0][0], m1.Val[0][0] - m2.Val[0][0]);
    EXPECT_EQ(mSub.Val[0][1], m1.Val[0][1] - m2.Val[0][1]);
    EXPECT_EQ(mSub.Val[1][0], m1.Val[1][0] - m2.Val[1][0]);
    EXPECT_EQ(mSub.Val[1][1], m1.Val[1][1] - m2.Val[1][1]);
}

TEST_P(MatrixFloatFixture, MatFloatSubTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2F mSub = m1 - m2;

    // Check that substraction of 2 matrices is correct
    EXPECT_EQ(mSub.Val[0][0], m1.Val[0][0] - m2.Val[0][0]);
    EXPECT_EQ(mSub.Val[0][1], m1.Val[0][1] - m2.Val[0][1]);
    EXPECT_EQ(mSub.Val[1][0], m1.Val[1][0] - m2.Val[1][0]);
    EXPECT_EQ(mSub.Val[1][1], m1.Val[1][1] - m2.Val[1][1]);
}

TEST_P(MatrixIntFixture, MatIntSubEqualTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2I mSub = m1;

    mSub -= m2;

    // Check that matrix -= matrix is correct
    EXPECT_EQ(mSub.Val[0][0], m1.Val[0][0] - m2.Val[0][0]);
    EXPECT_EQ(mSub.Val[0][1], m1.Val[0][1] - m2.Val[0][1]);
    EXPECT_EQ(mSub.Val[1][0], m1.Val[1][0] - m2.Val[1][0]);
    EXPECT_EQ(mSub.Val[1][1], m1.Val[1][1] - m2.Val[1][1]);
}

TEST_P(MatrixFloatFixture, MatFloatSubEqualTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2F mSub = m1;

    mSub -= m2;

    // Check that matrix -= matrix is correct
    EXPECT_EQ(mSub.Val[0][0], m1.Val[0][0] - m2.Val[0][0]);
    EXPECT_EQ(mSub.Val[0][1], m1.Val[0][1] - m2.Val[0][1]);
    EXPECT_EQ(mSub.Val[1][0], m1.Val[1][0] - m2.Val[1][0]);
    EXPECT_EQ(mSub.Val[1][1], m1.Val[1][1] - m2.Val[1][1]);
}

TEST_P(MatrixIntFixture, MatIntAndScalarMultiplyTest)
{
    auto m = GetParam();
    int scalar = 4;

    Mat2x2I mMul = m;
    mMul *= scalar;

    // Check that matrix *= scalar is correct
    EXPECT_EQ(mMul.Val[0][0], m.Val[0][0] * scalar);
    EXPECT_EQ(mMul.Val[0][1], m.Val[0][1] * scalar);
    EXPECT_EQ(mMul.Val[1][0], m.Val[1][0] * scalar);
    EXPECT_EQ(mMul.Val[1][1], m.Val[1][1] * scalar);
}

TEST_P(MatrixFloatFixture, MatFloatAndScalarMultiplyTest)
{
    auto m = GetParam();
    float scalar = 4.4f;

    Mat2x2F mMul = m;
    mMul *= scalar;

    // Check that matrix *= scalar is correct
    EXPECT_EQ(mMul.Val[0][0], m.Val[0][0] * scalar);
    EXPECT_EQ(mMul.Val[0][1], m.Val[0][1] * scalar);
    EXPECT_EQ(mMul.Val[1][0], m.Val[1][0] * scalar);
    EXPECT_EQ(mMul.Val[1][1], m.Val[1][1] * scalar);
}

TEST_P(MatrixIntFixture, IntMatxMatMultiplyTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2I mMul = m1 * m2;

    // Check that the multiplication of a matrix by a matrix is correct
    EXPECT_EQ(mMul.Val[0][0], m1.Val[0][0] * m2.Val[0][0] + m1.Val[0][1] * m2.Val[1][0]);
    EXPECT_EQ(mMul.Val[0][1], m1.Val[0][0] * m2.Val[0][1] + m1.Val[0][1] * m2.Val[1][1]);
    EXPECT_EQ(mMul.Val[1][0], m1.Val[1][0] * m2.Val[0][0] + m1.Val[1][1] * m2.Val[1][0]);
    EXPECT_EQ(mMul.Val[1][1], m1.Val[1][0] * m2.Val[0][1] + m1.Val[1][1] * m2.Val[1][1]);
}

TEST_P(MatrixFloatFixture, FloatMatxMatMultiplyTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2F mMul = m1 * m2;

    // Check that the multiplication of a matrix by a matrix is correct
    EXPECT_EQ(mMul.Val[0][0], m1.Val[0][0] * m2.Val[0][0] + m1.Val[0][1] * m2.Val[1][0]);
    EXPECT_EQ(mMul.Val[0][1], m1.Val[0][0] * m2.Val[0][1] + m1.Val[0][1] * m2.Val[1][1]);
    EXPECT_EQ(mMul.Val[1][0], m1.Val[1][0] * m2.Val[0][0] + m1.Val[1][1] * m2.Val[1][0]);
    EXPECT_EQ(mMul.Val[1][1], m1.Val[1][0] * m2.Val[0][1] + m1.Val[1][1] * m2.Val[1][1]);
}

TEST_P(MatrixIntFixture, IntMatxMatMultiplyEqualTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2I mTest = m1;
    mTest *= m2;

    // Check that the multiplication of a matrix by a matrix is correct
    EXPECT_EQ(mTest.Val[0][0], m1.Val[0][0] * m2.Val[0][0] + m1.Val[0][1] * m2.Val[1][0]);
    EXPECT_EQ(mTest.Val[0][1], m1.Val[0][0] * m2.Val[0][1] + m1.Val[0][1] * m2.Val[1][1]);
    EXPECT_EQ(mTest.Val[1][0], m1.Val[1][0] * m2.Val[0][0] + m1.Val[1][1] * m2.Val[1][0]);
    EXPECT_EQ(mTest.Val[1][1], m1.Val[1][0] * m2.Val[0][1] + m1.Val[1][1] * m2.Val[1][1]);
}

TEST_P(MatrixFloatFixture, FloatMatxMatMultiplyEqualTest)
{
    auto m1 = GetParam();
    auto m2 = GetParam();

    Mat2x2F mTest = m1;
    mTest *= m2;

    // Check that the multiplication of a matrix by a matrix is correct
    EXPECT_EQ(mTest.Val[0][0], m1.Val[0][0] * m2.Val[0][0] + m1.Val[0][1] * m2.Val[1][0]);
    EXPECT_EQ(mTest.Val[0][1], m1.Val[0][0] * m2.Val[0][1] + m1.Val[0][1] * m2.Val[1][1]);
    EXPECT_EQ(mTest.Val[1][0], m1.Val[1][0] * m2.Val[0][0] + m1.Val[1][1] * m2.Val[1][0]);
    EXPECT_EQ(mTest.Val[1][1], m1.Val[1][0] * m2.Val[0][1] + m1.Val[1][1] * m2.Val[1][1]);
}

TEST_P(MatrixIntFixture, MatIntxVecMultiplyTest)
{
    auto m = GetParam();
    Vec2I v(4, 1);

    Vec2I vMul = m * v;

    // Check that the multiplication of a matrix by a matrix is correct
    EXPECT_EQ(vMul.X, m.Val[0][0] * v.X + m.Val[0][1] * v.Y);
    EXPECT_EQ(vMul.Y, m.Val[1][0] * v.X + m.Val[1][1] * v.Y);
}

TEST_P(MatrixFloatFixture, MatFloatxVecMultiplyTest)
{
    auto m = GetParam();
    Vec2F v(4, 1);

    Vec2F vMul = m * v;

    // Check that the multiplication of a matrix by a matrix is correct
    EXPECT_EQ(vMul.X, m.Val[0][0] * v.X + m.Val[0][1] * v.Y);
    EXPECT_EQ(vMul.Y, m.Val[1][0] * v.X + m.Val[1][1] * v.Y);
}