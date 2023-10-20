#include "Utility.h"
#include "Vec3.h"

#include "gtest/gtest.h"

using namespace Math;

struct Vec3IntFixture : public ::testing::TestWithParam<int>
{
};

INSTANTIATE_TEST_SUITE_P(Vec3, Vec3IntFixture, testing::Values(
        1, 2, 3, 4, 5, -2, -4, 8, 22, 50, 56, -65, -87
));

#pragma region Vec3 int Operator

TEST (Vec3, IntCreationWithNoArgument)
{
    Math::Vec3I vec;
    EXPECT_EQ(vec.X, 0);
    EXPECT_EQ(vec.Y, 0);
    EXPECT_EQ(vec.Z, 0);
}

TEST_P(Vec3IntFixture, IntCreationWithArgument)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vec(values, values, values);
    EXPECT_EQ(vec.X, values);
    EXPECT_EQ(vec.Y, values);
    EXPECT_EQ(vec.Z, values);
}

TEST_P(Vec3IntFixture, IntAddition)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(values, values, values);
    Math::Vec3I vec = vecA + vecB;
    EXPECT_EQ(vec.X, vecA.X + vecB.X);
    EXPECT_EQ(vec.Y, vecA.Y + vecB.Y);
    EXPECT_EQ(vec.Z, vecA.Z + vecB.Z);
}

TEST_P(Vec3IntFixture, IntSubstract)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(values, values, values);
    Math::Vec3I vec = vecA - vecB;
    EXPECT_EQ(vec.X, vecA.X - vecB.X);
    EXPECT_EQ(vec.Y, vecA.Y - vecB.Y);
    EXPECT_EQ(vec.Z, vecA.Z - vecB.Z);
}

TEST_P(Vec3IntFixture, IntMultiplyMinusOne)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vec =- vecA;
    EXPECT_EQ(vec.X, -vecA.X);
    EXPECT_EQ(vec.Y, -vecA.Y);
    EXPECT_EQ(vec.Z, -vecA.Z);
}

TEST_P(Vec3IntFixture, IntPlusEqualOperator)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(values, values, values);
    vecA += vecB;
    EXPECT_EQ(vecA.X, values + vecB.X);
    EXPECT_EQ(vecA.Y, values + vecB.Y);
    EXPECT_EQ(vecA.Z, values + vecB.Z);
}

TEST_P(Vec3IntFixture, IntMinusEqualOperator)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(values, values, values);
    vecA -= vecB;
    EXPECT_EQ(vecA.X, values - vecB.X);
    EXPECT_EQ(vecA.Y, values - vecB.Y);
    EXPECT_EQ(vecA.Z, values - vecB.Z);
}

TEST_P(Vec3IntFixture, IntMultiplyWithScalar)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vec = vecA * 22;
    EXPECT_EQ(vec.X, 22 * vecA.X);
    EXPECT_EQ(vec.Y, 22 * vecA.Y);
    EXPECT_EQ(vec.Z, 22 * vecA.Z);
}

TEST_P(Vec3IntFixture, IntDivisionWithScalar)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vec = vecA / 22;
    EXPECT_EQ(vec.X, vecA.X/22);
    EXPECT_EQ(vec.Y, vecA.Y/22);
    EXPECT_EQ(vec.Z, vecA.Z/22);
}

TEST_P(Vec3IntFixture, IntMulEqualOperator)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    vecA *= 25;
    EXPECT_EQ(vecA.X, values * 25);
    EXPECT_EQ(vecA.Y, values * 25);
    EXPECT_EQ(vecA.Z, values * 25);
}

TEST_P(Vec3IntFixture, IntDivEqualOperator)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    vecA /= 25;
    EXPECT_EQ(vecA.X, values / 25);
    EXPECT_EQ(vecA.Y, values / 25);
    EXPECT_EQ(vecA.Z, values / 25);
}

TEST (Vec3, IntEqualFalse)
{
    Math::Vec3I vecA(1, 2, -3);
    Math::Vec3I vecB(4, -3, 2);
    EXPECT_FALSE(vecA == vecB);
}

TEST_P(Vec3IntFixture, IntEqualTrue)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(values, values, values);
    EXPECT_TRUE(vecA == vecB);
}

TEST_P(Vec3IntFixture, IntInequalFalse)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(values, values, values);
    EXPECT_FALSE(vecA != vecB);
}

TEST (Vec3, IntInequalTrue)
{
    Math::Vec3I vecA(1, 56, -22);
    Math::Vec3I vecB(1, 2, -3);
    EXPECT_TRUE(vecA != vecB);
}

TEST_P(Vec3IntFixture, IntIndexOperator)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    EXPECT_EQ(vecA[0], vecA.X);
    EXPECT_EQ(vecA[1], vecA.Y);
    EXPECT_EQ(vecA[2], vecA.Z);
}

TEST_P(Vec3IntFixture, Cast)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vec(values, values, values);

    auto vecFloat = static_cast<Math::Vec3F>(vec);
    auto vecDouble = static_cast<Math::Vec3<double>>(vec);

    EXPECT_FLOAT_EQ(vecFloat.X, static_cast<float>(vec.X));
    EXPECT_FLOAT_EQ(vecFloat.Y, static_cast<float>(vec.Y));
    EXPECT_FLOAT_EQ(vecFloat.Z, static_cast<float>(vec.Z));
    EXPECT_DOUBLE_EQ(vecDouble.X, static_cast<double>(vec.X));
    EXPECT_DOUBLE_EQ(vecDouble.Y, static_cast<double>(vec.Y));
    EXPECT_DOUBLE_EQ(vecDouble.Z, static_cast<double>(vec.Z));
}

#pragma endregion

struct Vec3FloatFixture : public ::testing::TestWithParam<float>
{
};

INSTANTIATE_TEST_SUITE_P(Vec3, Vec3FloatFixture, testing::Values(
        1.1, 2.2, 3.3, 4.4, 5.5, -2.2, -4.2, 8.1, 22.2, 50.2, 56.6, -65.4, -87.3
));

#pragma region Vec3 float Operator

TEST (Vec3, Vector3FloatCreationWithNoArgument)
{
    Math::Vec3F vec;
    EXPECT_FLOAT_EQ(vec.X, 0.0f);
    EXPECT_FLOAT_EQ(vec.Y,  0.0f);
    EXPECT_FLOAT_EQ(vec.Z,  0.0f);
}

TEST_P(Vec3FloatFixture, IntCreationWithArgument)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vec(values, values, values);
    EXPECT_EQ(vec.X, values);
    EXPECT_EQ(vec.Y, values);
    EXPECT_EQ(vec.Z, values);
}

TEST_P(Vec3FloatFixture, IntAddition)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(values, values, values);
    Math::Vec3F vec = vecA + vecB;
    EXPECT_EQ(vec.X, vecA.X + vecB.X);
    EXPECT_EQ(vec.Y, vecA.Y + vecB.Y);
    EXPECT_EQ(vec.Z, vecA.Z + vecB.Z);
}

TEST_P(Vec3FloatFixture, IntSubstract)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(values, values, values);
    Math::Vec3F vec = vecA - vecB;
    EXPECT_EQ(vec.X, vecA.X - vecB.X);
    EXPECT_EQ(vec.Y, vecA.Y - vecB.Y);
    EXPECT_EQ(vec.Z, vecA.Z - vecB.Z);
}

TEST_P(Vec3FloatFixture, IntMultiplyMinusOne)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vec =- vecA;
    EXPECT_EQ(vec.X, -vecA.X);
    EXPECT_EQ(vec.Y, -vecA.Y);
    EXPECT_EQ(vec.Z, -vecA.Z);
}

TEST_P(Vec3FloatFixture, IntPlusEqualOperator)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(values, values, values);
    vecA += vecB;
    EXPECT_EQ(vecA.X, values + vecB.X);
    EXPECT_EQ(vecA.Y, values + vecB.Y);
    EXPECT_EQ(vecA.Z, values + vecB.Z);
}

TEST_P(Vec3FloatFixture, IntMinusEqualOperator)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(values, values, values);
    vecA -= vecB;
    EXPECT_EQ(vecA.X, values - vecB.X);
    EXPECT_EQ(vecA.Y, values - vecB.Y);
    EXPECT_EQ(vecA.Z, values - vecB.Z);
}

TEST_P(Vec3FloatFixture, IntMultiplyWithScalar)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vec = vecA * 22;
    EXPECT_EQ(vec.X, 22 * vecA.X);
    EXPECT_EQ(vec.Y, 22 * vecA.Y);
    EXPECT_EQ(vec.Z, 22 * vecA.Z);
}

TEST_P(Vec3FloatFixture, IntDivisionWithScalar)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vec = vecA / 22.f;

    EXPECT_FLOAT_EQ(vec.X, vecA.X / 22.f);
    EXPECT_FLOAT_EQ(vec.Y, vecA.Y / 22.f);
    EXPECT_FLOAT_EQ(vec.Z, vecA.Z / 22.f);
}

TEST_P(Vec3FloatFixture, IntMulEqualOperator)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    vecA *= 25;
    EXPECT_EQ(vecA.X, values * 25);
    EXPECT_EQ(vecA.Y, values * 25);
    EXPECT_EQ(vecA.Z, values * 25);
}

TEST_P(Vec3FloatFixture, IntDivEqualOperator)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    vecA /= 25;
	EXPECT_FLOAT_EQ(vecA.X, values / 25);
	EXPECT_FLOAT_EQ(vecA.Y, values / 25);
	EXPECT_FLOAT_EQ(vecA.Z, values / 25);
}

TEST (Vec3, Vector3floatEqualFalse)
{
    Math::Vec3F vecA(1.1, 2.2, -3);
    Math::Vec3F vecB(4, -3.3, 2);
    EXPECT_FALSE(vecA == vecB);
}

TEST_P(Vec3FloatFixture, Vector3floatEqualTrue)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(values, values, values);
    EXPECT_TRUE(vecA == vecB);
}

TEST_P(Vec3FloatFixture, Vector3floatInequalFalse)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(values, values, values);
    EXPECT_FALSE(vecA != vecB);
}

TEST (Vec3, Vector3floatInequalTrue)
{
    Math::Vec3F vecA(1.1, 56.4, -22);
    Math::Vec3F vecB(1.1, 2, -3.3);
    EXPECT_TRUE(vecA != vecB);
}

TEST_P(Vec3FloatFixture, IndexOperator)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    EXPECT_FLOAT_EQ(vecA[0], vecA.X);
    EXPECT_FLOAT_EQ(vecA[1], vecA.Y);
    EXPECT_FLOAT_EQ(vecA[2], vecA.Z);
}
#pragma endregion

#pragma region Vec3 utility Functions

TEST_P(Vec3IntFixture, DotProduct){
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(1, 20, -30);
    float dotResult = Math::Vec3I::Dot(vecA, vecB);
    EXPECT_FLOAT_EQ(dotResult, vecA.X * vecB.X + vecA.Y * vecB.Y + vecA.Z * vecB.Z);
}

TEST_P(Vec3FloatFixture, DotProduct){
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1.1, 20.2, -30);
    float dotResult = Math::Vec3F::Dot(vecA, vecB);
    EXPECT_FLOAT_EQ(dotResult, vecA.X * vecB.X + vecA.Y * vecB.Y + vecA.Z * vecB.Z);
}

TEST_P(Vec3IntFixture, Length){
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vec(values, values, values);
    const int length = vec.Length<int>();
    EXPECT_EQ(length, static_cast<int> (std::sqrt(vec.X * vec.X + vec.Y * vec.Y + vec.Z * vec.Z)));
}

TEST_P(Vec3FloatFixture, Length){
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vec(values, values, values);
    float length = vec.Length<float>();
    EXPECT_FLOAT_EQ(length, std::sqrt(vec.X * vec.X + vec.Y * vec.Y + vec.Z * vec.Z));
}

TEST_P(Vec3IntFixture, Projection){
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(1, 22, -4);
    int projection = vecA.Project<int>(vecB);

    EXPECT_EQ(projection, static_cast<int>(vecA.Dot(vecA, vecB)/vecB.Length<int>()));
}


TEST_P(Vec3FloatFixture, Projection){
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1, 22.2, -4.4);
    float projection = vecA.Project<float>(vecB);
    EXPECT_FLOAT_EQ(projection, vecA.Dot(vecA, vecB)/vecB.Length<float>());
}

TEST_P(Vec3IntFixture, Reflect){
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(1, 22, -4);
    Math::Vec3I vec = vecA.Reflect(vecB);

    Math::Vec3I vecBNormalized = Math::Vec3I::Normalized(vecB);
    float dotVecAndNormalized = (Math::Vec3I::Dot(vecA, vecBNormalized));
    Math::Vec3I calculationVec = vecBNormalized * (2*dotVecAndNormalized);

    EXPECT_EQ(vec, vecA - calculationVec);
}

TEST_P(Vec3FloatFixture, Reflect){
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1, 22.2, -4.4);
    Math::Vec3F vec = vecA.Reflect(vecB);
    Math::Vec3F vecBNormalized = Math::Vec3F::Normalized(vecB);
    float dotVecAndNormalized = (Math::Vec3F::Dot(vecA, vecBNormalized));
    Math::Vec3F calculationVec = vecBNormalized * (2*dotVecAndNormalized);
    EXPECT_EQ(vec, vecA - calculationVec);
}

TEST_P(Vec3IntFixture, Normalized){
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vec = Math::Vec3I::Normalized(vecA);

    EXPECT_EQ(vec, vecA/vecA.Length<int>());
}

TEST_P(Vec3FloatFixture, Normalized){
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vec = Math::Vec3F::Normalized(vecA);

    EXPECT_EQ(vec, vecA/vecA.Length<float>());
}


TEST_P(Vec3IntFixture, IsPerpendicular)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(1, 2, -3);
    bool isPerpendicular = Math::Vec3I::IsPerpendicular(vecA, vecB);

    EXPECT_TRUE(isPerpendicular == (Math::Vec3I::Dot(vecA, vecB) == 0));
}

TEST_P(Vec3FloatFixture, IsPerpendicular)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1.1, 2.2, -3);
    bool isPerpendicular = Math::Vec3F::IsPerpendicular(vecA, vecB);

    EXPECT_TRUE(isPerpendicular == (Math::Vec3F::Dot(vecA, vecB) == 0));
}

TEST_P(Vec3IntFixture, IsParallel)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(1, 2, -3);
    bool isParallel = Math::Vec3I::IsParallel(vecA,vecB);
    EXPECT_TRUE(isParallel == (Math::Vec3I::Dot(vecA,vecB) == 0));
}

TEST_P(Vec3FloatFixture, IsParallel)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1, 2.2, -3);
    bool isParallel = Math::Vec3F::IsParallel(vecA,vecB);
    EXPECT_TRUE(isParallel == (Math::Vec3F::Dot(vecA,vecB) == 0));
}

TEST_P(Vec3IntFixture, Lerp)
{
    float time = 0.5f;
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(1, 2, -3);
    Math::Vec3I vec = Math::Vec3I::Lerp(vecA, vecB, time);

    Math::Vec3I vecCalculation = vecB - vecA;
    vecCalculation *= (int)time;

    EXPECT_EQ(vec, vecA + vecCalculation);
}

TEST_P(Vec3FloatFixture, Lerp)
{
    float time = 0.5f;
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1.1, 2.2, -3);
    Math::Vec3F vec = Math::Vec3F::Lerp(vecA, vecB, time);

    Math::Vec3F vecCalculation = vecB - vecA;
    vecCalculation *= (float)time;

    EXPECT_EQ(vec, vecA + vecCalculation);
}

TEST_P(Vec3IntFixture, GetAngle)
{
    auto values = Vec3IntFixture::GetParam();
    Math::Vec3I vecA(values, values, values);
    Math::Vec3I vecB(1, 2, -3);
    auto omega = static_cast<float>(Math::Vec3I::GetVectorAngle(vecA, vecB));
    EXPECT_NEAR(omega, std::acos(Math::Vec3I::Dot(vecA, vecB) / (vecA.Length<int>() * vecB.Length<int>())), Math::Epsilon);
}

TEST_P(Vec3FloatFixture, GetAngle)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1, 2.2, -3);
    auto omega = static_cast<float>(Math::Vec3F::GetVectorAngle(vecA, vecB));
    EXPECT_NEAR(omega, std::acos(Math::Vec3F::Dot(vecA, vecB) / (vecA.Length<float>() * vecB.Length<float>())), Math::Epsilon);
}

TEST_P(Vec3FloatFixture, Slerp)
{
    float time = 0.5f;
    auto values = Vec3FloatFixture::GetParam();

    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1, 2, -3);
    Math::Vec3F vec = Math::Vec3F::Slerp(vecA, vecB, time);

    auto omega = Math::Vec3F::GetVectorAngle(vecA, vecB);
    auto calculation = (Math::Sin(omega * (1-time))/Math::Sin(omega));
    Math::Vec3F vecZ(vecA.X * calculation, vecA.Y * calculation, vecA.Z * calculation);
    auto cal = Math::Sin(time * omega)/Math::Sin(omega);
    vecZ = vecZ + vecB * cal;

    EXPECT_NEAR(vec.X, vecZ.X, Math::Epsilon);
    EXPECT_NEAR(vec.Y, vecZ.Y, Math::Epsilon);
    EXPECT_NEAR(vec.Z, vecZ.Z, Math::Epsilon);
}

TEST_P(Vec3FloatFixture, Distance)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1, 2, -3);
    float distance = Math::Vec3F::Distance<float>(vecA, vecB);

    EXPECT_FLOAT_EQ(distance, (vecA - vecB).Length<float>());
}

TEST_P(Vec3FloatFixture, CrossProduct)
{
    auto values = Vec3FloatFixture::GetParam();
    Math::Vec3F vecA(values, values, values);
    Math::Vec3F vecB(1, 2, -3);
    Math::Vec3F crossProduct = Math::Vec3F::CrossProduct(vecA, vecB);
    Math::Vec3F vecCP(vecA.Y*vecB.Z - vecA.Z*vecB.Y, vecA.Z*vecB.X - vecA.X*vecB.Z, vecA.X*vecB.Y - vecA.Y*vecB.X);

	EXPECT_FLOAT_EQ(crossProduct.X, vecCP.X);
	EXPECT_FLOAT_EQ(crossProduct.Y, vecCP.Y);
	EXPECT_FLOAT_EQ(crossProduct.Z, vecCP.Z);
}
#pragma endregion


