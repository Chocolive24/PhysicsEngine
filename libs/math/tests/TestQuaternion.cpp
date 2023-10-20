/**
 * @author Olivier
 */

#include "Quaternion.h"

#include "gtest/gtest.h"

#include <array>

using namespace Math;

struct ConstructorWithFloatValuesFixture : public ::testing::TestWithParam<std::array<float, 4>>{};

struct QuaternionFloatOperationsFixture : public ::testing::TestWithParam<std::pair<QuaternionF, QuaternionF>>{};

struct QuaternionFloatFixture : public ::testing::TestWithParam<QuaternionF>{};

struct QuaternionAndVectorFloatOperationFixture : public ::testing::TestWithParam<std::pair<QuaternionF, Vec3F>>{};

struct AngleAxisFloatFixture : public ::testing::TestWithParam<std::pair<Radian, Vec3F>>{};

struct ArrayOfAngleFixture : public ::testing::TestWithParam<std::array<Radian, 3>> {};

INSTANTIATE_TEST_SUITE_P(QuaternionF, ConstructorWithFloatValuesFixture, testing::Values(
        std::array<float, 4>{1.f, 15.332f, 21.f, 0.8887f},
        std::array<float, 4>{13.4567f, 0.876542f, 22.f, 100.543f},
        std::array<float, 4>{0.f, 0.f, 0.0000f, 0.f}
        ));

INSTANTIATE_TEST_SUITE_P(QuaternionF, QuaternionFloatOperationsFixture, testing::Values(
        std::pair{QuaternionF(1.f, 0.f, 0.f, 0.f),
                  QuaternionF(10.234f, 23.f, 3.2311f, 0.00001f)},
        std::pair{QuaternionF(-11.34f, -1.f, -321.f, -0000.1f),
                  QuaternionF(9.45f, -87.f, 21.f, -0.98f)},
        std::pair{QuaternionF(0.f, 0.f, 0.f, 0.f),
                  QuaternionF(100.9384f, 10.f, 3.24f, 2.111f)}
        ));

INSTANTIATE_TEST_SUITE_P(QuaternionF, QuaternionAndVectorFloatOperationFixture, testing::Values(
    std::pair{QuaternionF(1.f, 0.f, 1.f, 0.f), Vec3F(5.0f, 10.0f, 4.0f)}
));

INSTANTIATE_TEST_SUITE_P(QuaternionF, QuaternionFloatFixture, testing::Values(
    QuaternionF(13.345f, 23.213f, 56.f, 0.000001f),
    QuaternionF(1.f, 0.f, 0.f, 0.f)
));

INSTANTIATE_TEST_SUITE_P(QuaternionF, AngleAxisFloatFixture, testing::Values(
    std::pair{static_cast<Radian>(Degree(65.f)), Vec3F(0, 1, 0)},
    std::pair{static_cast<Radian>(Degree(345.f)), Vec3F(1, 0, 0)},
    std::pair{static_cast<Radian>(Degree(197.f)), Vec3F(0, 0, 1)},
    std::pair{static_cast<Radian>(Degree(45.f)), Vec3F(10, 24, 100)},
    std::pair{static_cast<Radian>(Degree(123.f)), Vec3F(-5, -245, -123)},
    std::pair{static_cast<Radian>(Degree(-245.f)), Vec3F(1, 0, 0)},
    std::pair{static_cast<Radian>(Degree(650.f)), Vec3F(0, 1, 0)},
    std::pair{static_cast<Radian>(Degree(-890.f)), Vec3F(0, 0, 1)},
    std::pair{static_cast<Radian>(Degree(-1298.454f)), Vec3F(178, -54.32f, -0.00009f)}
));

INSTANTIATE_TEST_SUITE_P(QuaternionF, ArrayOfAngleFixture, testing::Values(
        std::array<Radian, 3>{ static_cast<Radian>(Degree(0.f)),
                               static_cast<Radian>(Degree(0.f)),
                               static_cast<Radian>(Degree(0.f)) },

        std::array<Radian, 3>{ static_cast<Radian>(Degree(135.f)),
                               static_cast<Radian>(Degree(65.f)),
                               static_cast<Radian>(Degree(341.f)) },

        std::array<Radian, 3>{ static_cast<Radian>(Degree(-95.f)),
                               static_cast<Radian>(Degree(-198.f)),
                               static_cast<Radian>(Degree(-249.f)) },

        std::array<Radian, 3>{ static_cast<Radian>(Degree(995.f)),
                               static_cast<Radian>(Degree(720.f)),
                               static_cast<Radian>(Degree(1456.f)) },

        std::array<Radian, 3>{ static_cast<Radian>(Degree(-695.f)),
                               static_cast<Radian>(Degree(-1198.f)),
                               static_cast<Radian>(Degree(-949.f)) },

        std::array<Radian, 3>{ static_cast<Radian>(Degree(-95.654f)),
                               static_cast<Radian>(Degree(-198.9843f)),
                               static_cast<Radian>(Degree(-249.1111f)) }
));

TEST(Constructor, Default)
{
    QuaternionI q;

    EXPECT_EQ(q.W, 1);
    EXPECT_EQ(q.V.X, 0);
    EXPECT_EQ(q.V.Y, 0);
    EXPECT_EQ(q.V.Z, 0);
}

TEST_P(ConstructorWithFloatValuesFixture, ConstructorWithFloat)
{
    auto val = GetParam();

    QuaternionF q(val[0], val[1], val[2], val[3]);

    EXPECT_FLOAT_EQ(q.W, val[0]);
    EXPECT_FLOAT_EQ(q.V.X, val[1]);
    EXPECT_FLOAT_EQ(q.V.Y, val[2]);
    EXPECT_FLOAT_EQ(q.V.Z, val[3]);
}

TEST(ConstexprFunctions, Identitiy)
{
    QuaternionI q = QuaternionI::Identity();

    EXPECT_EQ(q.W, 1);
    EXPECT_EQ(q.V.X, 0);
    EXPECT_EQ(q.V.Y, 0);
    EXPECT_EQ(q.V.Z, 0);
}

TEST_P(QuaternionFloatOperationsFixture, Multiplication)
{
    auto [q1, q2] = GetParam();

    QuaternionF q1q2 = q1 * q2;
    QuaternionF q2q1 = q2 * q1;

    QuaternionF q1TimeEqualQ2 = q1;
    q1TimeEqualQ2 *= q2;

    auto q1q2V = (q2.W * q1.V) + (q1.W * q2.V) + Vec3<float>::CrossProduct(q1.V, q2.V);
    auto q2q1V = (q1.W * q2.V) + (q2.W * q1.V) + Vec3<float>::CrossProduct(q2.V, q1.V);

    EXPECT_FLOAT_EQ(q1q2.W, (q1.W * q2.W) - Vec3<float>::Dot(q1.V, q2.V));
    EXPECT_FLOAT_EQ(q2q1.W, (q1.W * q2.W) - Vec3<float>::Dot(q1.V, q2.V));

    EXPECT_FLOAT_EQ(q1TimeEqualQ2.W, (q1.W * q2.W) - Vec3<float>::Dot(q1.V, q2.V));

    for (int i = 0; i < 3; i++)
    {
        EXPECT_FLOAT_EQ(q1q2.V[i], q1q2V[i]);
        EXPECT_FLOAT_EQ(q2q1.V[i], q2q1V[i]);

        EXPECT_FLOAT_EQ(q1TimeEqualQ2.V[i], q1q2V[i]);
    }
}

TEST_P(QuaternionAndVectorFloatOperationFixture, Multiplication)
{
    auto [q, v] = GetParam();

    auto qV = q * v;
    auto vQ = v * q;
    auto vTimeEqualQ = v;
    vTimeEqualQ *= q;

    QuaternionF qNorm = q.Normalized<float>();

    auto vExpected = v + 2 * qNorm.W * Vec3<float>::CrossProduct(qNorm.V, v) + 2 *
    Vec3<float>::CrossProduct(qNorm.V, Vec3<float>::CrossProduct(qNorm.V, v));

    for (int i = 0; i < 3; i++)
    {
        EXPECT_NEAR(qV[i], vExpected[i], Epsilon);
        EXPECT_NEAR(vQ[i], vExpected[i], Epsilon);
        EXPECT_NEAR(vTimeEqualQ[i], vExpected[i], Epsilon);
    }
}

TEST_P(QuaternionFloatFixture, Cast)
{
    auto q = GetParam();

    auto qInt = static_cast<QuaternionI>(q);
    auto qDouble = static_cast<Quaternion<double>>(q);

    EXPECT_EQ(qInt.W, static_cast<int>(q.W));
    EXPECT_DOUBLE_EQ(qDouble.W, static_cast<double>(q.W));

    for(int i = 0; i < 3; i++)
    {
        EXPECT_EQ(qInt.V[i], static_cast<int>(q.V[i]));
        EXPECT_DOUBLE_EQ(qDouble.V[i], static_cast<double>(q.V[i]));
    }
}

TEST_P(QuaternionFloatFixture, Magnitude)
{
    auto q = GetParam();

    auto magnitude = q.Magnitude<float>();

    EXPECT_FLOAT_EQ(magnitude, std::sqrt(q.W * q.W + q.V.X * q.V.X + q.V.Y * q.V.Y + q.V.Z * q.V.Z));
}

TEST_P(QuaternionFloatFixture, Normalization)
{
    auto q = GetParam();
    auto magnitude = q.Magnitude<float>();
    QuaternionF qNorm;
    QuaternionF normalizeCorrect = q;

    if (magnitude == 0)
    {
        EXPECT_THROW(qNorm = q.Normalized<float>(), DivisionByZeroException);
        EXPECT_THROW(q.Normalize<float>(), DivisionByZeroException);
        return;
    }

    auto inverseMagnitude = 1 / magnitude;
    qNorm = q.Normalized<float>();
    normalizeCorrect.Normalize<float>();

    EXPECT_FLOAT_EQ(qNorm.W, q.W * inverseMagnitude);
    EXPECT_FLOAT_EQ(normalizeCorrect.W, q.W * inverseMagnitude);

    for (int i = 0; i < 3; i++)
    {
        EXPECT_FLOAT_EQ(qNorm.V[i], q.V[i] * inverseMagnitude);
        EXPECT_FLOAT_EQ(normalizeCorrect.V[i], q.V[i] * inverseMagnitude);
    }
}

TEST_P(AngleAxisFloatFixture, AngleAxis)
{
    auto [angle, axis] = GetParam();

    auto length = axis.Length<float>();
    Vec3F axisNorm;

    if (length == 0)
    {
        EXPECT_THROW(axisNorm = Vec3F::Normalized(axis), DivisionByZeroException);
        return;
    }

    QuaternionF q = QuaternionF::AngleAxis<float>(angle, axis);

    axisNorm = Vec3F::Normalized(axis);

    EXPECT_FLOAT_EQ(q.W, Cos(angle / 2.f));
    EXPECT_FLOAT_EQ(q.V.X, axisNorm.X * Sin(angle / 2.f));
    EXPECT_FLOAT_EQ(q.V.Y, axisNorm.Y * Sin(angle / 2.f));
    EXPECT_FLOAT_EQ(q.V.Z, axisNorm.Z * Sin(angle / 2.f));
}

TEST_P(ArrayOfAngleFixture, EulerMethod)
{
    auto angles = GetParam();

    auto q = QuaternionF::Euler<float>(angles[0], angles[1], angles[2]);

    float cosX = Cos(angles[0] * 0.5);
    float sinX = Sin(angles[0] * 0.5);
    float cosY = Cos(angles[1] * 0.5);
    float sinY = Sin(angles[1] * 0.5);
    float cosZ = Cos(angles[2] * 0.5);
    float sinZ = Sin(angles[2] * 0.5);

    QuaternionF qExpected;
    qExpected.W = cosX * cosY * cosZ + sinX * sinY * sinZ;
    qExpected.V.X = sinX * cosY * cosZ - cosX * sinY * sinZ;
    qExpected.V.Y = cosX * sinY * cosZ + sinX * cosY * sinZ;
    qExpected.V.Z = cosX * cosY * sinZ - sinX * sinY * cosZ;

    EXPECT_FLOAT_EQ(q.W, qExpected.W);

    for(int i = 0; i < 3; i++)
    {
        EXPECT_FLOAT_EQ(q.V[i], qExpected.V[i]);
        EXPECT_FLOAT_EQ(q.V[i], qExpected.V[i]);
        EXPECT_FLOAT_EQ(q.V[i], qExpected.V[i]);
    }
}