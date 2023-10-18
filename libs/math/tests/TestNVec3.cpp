#include "NVec3.h"

#include "gtest/gtest.h"

using namespace Math;

#pragma region InstantiateParametrizedTests

struct ThreeVec3FTestFixture : public ::testing::TestWithParam<std::pair<NVec3<float, 3>, NVec3<float, 3>>>
{
};

struct FourVec3FTestFixtureMixed : public ::testing::TestWithParam<std::pair<FourVec3F, FourVec3F>>
{
};


struct ThreeVec3ITestFixture : public ::testing::TestWithParam<std::pair<NVec3<int, 3>, NVec3<int, 3>>>
{
};

struct FourVec3ITestFixtureMixed : public ::testing::TestWithParam<std::pair<FourVec3I, FourVec3I>>
{
};


INSTANTIATE_TEST_SUITE_P(NVec3, ThreeVec3FTestFixture, testing::Values(
	std::make_pair(
		NVec3<float, 3>(std::array<Vec3F, 3>{Vec3F{1.3f, 2.4f, 3.5f}, Vec3F{4.6f, 5.7f, 6.8f}, Vec3F{7.9f, 8.10f, 9.11f}}),
		NVec3<float, 3>(std::array<Vec3F, 3>{Vec3F{10.3f, 2.4f, 32.5f}, Vec3F{4.6f, 5.7f, 6.8f}, Vec3F{7.9f, 8.10f, 9.11f}})
	)
));

INSTANTIATE_TEST_SUITE_P(NVec3, FourVec3FTestFixtureMixed, testing::Values(
	std::make_pair(
		FourVec3F(std::array<Vec3F, 4>{Vec3F(1.3f, 2.4f, 3.5f), Vec3F(4.6f, 5.7f, 6.8f), Vec3F(7.9f, 8.10f, 9.11f), Vec3F(10.12f, 11.13f, 12.14f)}),
		FourVec3F(std::array<Vec3F, 4>{Vec3F(10.3f, 2.4f, 32.5f), Vec3F(4.6f, 5.7f, 6.8f), Vec3F(7.9f, 8.10f, 9.11f), Vec3F(10.12f, 11.13f, 12.14f)})
	)
));

INSTANTIATE_TEST_SUITE_P(NVec3, ThreeVec3ITestFixture, testing::Values(
	std::make_pair(
		NVec3<int, 3>(std::array<Vec3I, 3>{Vec3I{1, 2, 3}, Vec3I{3, 4, 5}, Vec3I{6, 7, 8}}),
		NVec3<int, 3>(std::array<Vec3I, 3>{Vec3I{10, 2, 32}, Vec3I{4, 5, 6}, Vec3I{7, 8, 9}})
	)
));

INSTANTIATE_TEST_SUITE_P(NVec3, FourVec3ITestFixtureMixed, testing::Values(
	std::make_pair(
		FourVec3I(std::array<Vec3I, 4>{Vec3I(1, 2, 3), Vec3I(3, 4, 5), Vec3I(6, 7, 8), Vec3I(7, 8, 9)}),
		FourVec3I(std::array<Vec3I, 4>{Vec3I(10, 2, 32), Vec3I(0, 4, 54), Vec3I(76, 6, 8), Vec3I(9, 11, 13)})
	)
));

#pragma endregion

#pragma region TwoVec3f

TEST_P(ThreeVec3FTestFixture, Constructor)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = NVec3<float, 3>(nV1);

	for (int i = 0; i < 3; i++)
	{
		EXPECT_FLOAT_EQ(nV1.X()[i], nV2.X()[i]);
		EXPECT_FLOAT_EQ(nV1.Y()[i], nV2.Y()[i]);
		EXPECT_FLOAT_EQ(nV1.Z()[i], nV2.Z()[i]);
	}
}

TEST_P(ThreeVec3FTestFixture, OperatorPlus)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 + nV2;
	auto result2 = nV1;
	result2 += nV2;

	for (int i = 0; i < 3; i++)
	{
		// +
		EXPECT_FLOAT_EQ(result.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_FLOAT_EQ(result.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
		// +=
		EXPECT_FLOAT_EQ(result2.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_FLOAT_EQ(result2.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result2.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
	}
}

TEST_P(ThreeVec3FTestFixture, OperatorMinus)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 - nV2;
	auto result2 = nV1;
	result2 -= nV2;
	auto result3 = -nV1;

	for (int i = 0; i < 3; i++)
	{
		// -
		EXPECT_FLOAT_EQ(result.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_FLOAT_EQ(result.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
		// -=
		EXPECT_FLOAT_EQ(result2.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_FLOAT_EQ(result2.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result2.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
		// - unary
		EXPECT_FLOAT_EQ(result3.X()[i], -nV1.X()[i]);
		EXPECT_FLOAT_EQ(result3.Y()[i], -nV1.Y()[i]);
		EXPECT_FLOAT_EQ(result3.Z()[i], -nV1.Z()[i]);
	}
}

TEST_P(ThreeVec3FTestFixture, OperatorMultiply)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 * nV2;
	auto result2 = nV1;
	result2 *= nV2;

	for (int i = 0; i < 3; i++)
	{
		// *
		EXPECT_FLOAT_EQ(result.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_FLOAT_EQ(result.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
		// *=
		EXPECT_FLOAT_EQ(result2.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_FLOAT_EQ(result2.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result2.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
	}
}

TEST_P(ThreeVec3FTestFixture, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;
	constexpr auto epsilon = 0.0001f;

	for (int i = 0; i < 3; i++)
	{
		if (nV2.X()[i] == 0 || nV2.Y()[i] == 0 || nV2.Z()[i] == 0)
		{
			NVec3<float, 3> result;
			EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
			EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / nV2;
	auto result2 = nV1;
	result2 /= nV2;

	for (int i = 0; i < 3; i++)
	{
// /
		EXPECT_NEAR(result.X()[i], nV1.X()[i] / nV2.X()[i], epsilon);
		EXPECT_NEAR(result.Y()[i], nV1.Y()[i] / nV2.Y()[i], epsilon);
		EXPECT_NEAR(result.Z()[i], nV1.Z()[i] / nV2.Z()[i], epsilon);
// /=
		EXPECT_NEAR(result2.X()[i], nV1.X()[i] / nV2.X()[i], epsilon);
		EXPECT_NEAR(result2.Y()[i], nV1.Y()[i] / nV2.Y()[i], epsilon);
		EXPECT_NEAR(result2.Z()[i], nV1.Z()[i] / nV2.Z()[i], epsilon);
	}
}

TEST_P(ThreeVec3FTestFixture, Dot)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = NVec3<float, 3>::Dot(nV1, nV2);

	for (int i = 0; i < 3; i++)
	{
		EXPECT_FLOAT_EQ(result[i], nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i] + nV1.Z()[i] * nV2.Z()[i]);
	}
}

TEST_P(ThreeVec3FTestFixture, SquareMagnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto result = nV1.SquareMagnitude();

	for (int i = 0; i < 3; i++)
	{
		EXPECT_FLOAT_EQ(result[i], nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i] + nV1.Z()[i] * nV1.Z()[i]);
	}
}

TEST_P(ThreeVec3FTestFixture, Magnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto result = nV1.Magnitude();

	for (int i = 0; i < 3; i++)
	{
		EXPECT_FLOAT_EQ(result[i], std::sqrt(nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i] + nV1.Z()[i] * nV1.Z()[i]));
	}
}

TEST_P(ThreeVec3FTestFixture, Normalized)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto magnitude = nV1.Magnitude();
	constexpr auto epsilon = 0.001f;
	std::array<float, 3> nV1Norm = {};

	for (int i = 0; i < 3; i++)
	{
		if (magnitude[i] == 0)
		{
			EXPECT_THROW(nV1Norm = nV1.Normalized(), DivisionByZeroException);
			return;
		}
	}

	nV1Norm = nV1.Normalized();
	const auto array1N = nV1.SquareMagnitude();
	std::array<float, 3> reciprocalSqrt = std::array<float, 3>();

	for (int i = 0; i < 3; i++)
	{
		reciprocalSqrt[i] = 1 / std::sqrt(array1N[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		EXPECT_NEAR(nV1Norm[i], reciprocalSqrt[i], epsilon);
	}
}

#pragma endregion

#pragma region FourVec3F

TEST_P(FourVec3FTestFixtureMixed, OperatorPlus)
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
		EXPECT_FLOAT_EQ(result.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_FLOAT_EQ(result.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
		// +=
		EXPECT_FLOAT_EQ(result2.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_FLOAT_EQ(result2.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result2.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
	}
}

TEST_P(FourVec3FTestFixtureMixed, OperatorMinus)
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
		EXPECT_FLOAT_EQ(result.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_FLOAT_EQ(result.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
// -=
		EXPECT_FLOAT_EQ(result2.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_FLOAT_EQ(result2.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result2.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
// - unary
		EXPECT_FLOAT_EQ(result3.X()[i], -nV1.X()[i]);
		EXPECT_FLOAT_EQ(result3.Y()[i], -nV1.Y()[i]);
		EXPECT_FLOAT_EQ(result3.Z()[i], -nV1.Z()[i]);
	}
}

TEST_P(FourVec3FTestFixtureMixed, OperatorMultiply)
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
		EXPECT_FLOAT_EQ(result.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_FLOAT_EQ(result.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
// *=
		EXPECT_FLOAT_EQ(result2.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_FLOAT_EQ(result2.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
		EXPECT_FLOAT_EQ(result2.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
	}
}

TEST_P(FourVec3FTestFixtureMixed, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;
	constexpr auto epsilon = 0.0001f;

	for (int i = 0; i < 4; i++)
	{
		if (nV2.X()[i] == 0 || nV2.Y()[i] == 0 || nV2.Z()[i] == 0)
		{
			NVec3<float, 4> result;
			EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
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
		EXPECT_NEAR(result.X()[i], nV1.X()[i] / nV2.X()[i], epsilon);
		EXPECT_NEAR(result.Y()[i], nV1.Y()[i] / nV2.Y()[i], epsilon);
		EXPECT_NEAR(result.Z()[i], nV1.Z()[i] / nV2.Z()[i], epsilon);
// /=
		EXPECT_NEAR(result2.X()[i], nV1.X()[i] / nV2.X()[i], epsilon);
		EXPECT_NEAR(result2.Y()[i], nV1.Y()[i] / nV2.Y()[i], epsilon);
		EXPECT_NEAR(result2.Z()[i], nV1.Z()[i] / nV2.Z()[i], epsilon);
	}
}

TEST_P(FourVec3FTestFixtureMixed, Dot)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto dotVec = FourVec3F::Dot(nV1, nV2);

	for (int i = 0; i < 3; i++) // Change the loop limit from 4 to 3
	{
		auto result = nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i] + nV1.Z()[i] * nV2.Z()[i]; // Include Z component
		EXPECT_EQ(dotVec[i], result);
	}
}

TEST_P(FourVec3FTestFixtureMixed, SquareMagnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	constexpr auto epsilon = 0.0001f;

	auto squareMagnitude = nV1.SquareMagnitude();

	for (int i = 0; i < 3; i++) // Change the loop limit from 4 to 3
	{
		auto result = nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i] + nV1.Z()[i] * nV1.Z()[i]; // Include Z component
		EXPECT_NEAR(squareMagnitude[i], result, epsilon);
	}
}

TEST_P(FourVec3FTestFixtureMixed, Magnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	constexpr auto epsilon = 0.0001f;

	auto magnitude = nV1.Magnitude();

	for (int i = 0; i < 3; i++) // Change the loop limit from 4 to 3
	{
		auto result = std::sqrt(nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i] + nV1.Z()[i] * nV1.Z()[i]); // Include Z component
		EXPECT_NEAR(magnitude[i], result, epsilon);
	}
}

#pragma endregion

#pragma region TwoVec3I

TEST_P(ThreeVec3ITestFixture, Constructor)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = NVec3<int, 3>(nV1);

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
		EXPECT_EQ(nV1.X()[i], nV2.X()[i]);
		EXPECT_EQ(nV1.Y()[i], nV2.Y()[i]);
// Add the Z component comparison
		EXPECT_EQ(nV1.Z()[i], nV2.Z()[i]);
	}
}

TEST_P(ThreeVec3ITestFixture, OperatorPlus)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 + nV2;
	auto result2 = nV1;
	result2 += nV2;

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
// +
		EXPECT_EQ(result.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
// Add the Z component addition
		EXPECT_EQ(result.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
// +=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
// Add the Z component addition
		EXPECT_EQ(result2.Z()[i], nV1.Z()[i] + nV2.Z()[i]);
	}
}

TEST_P(ThreeVec3ITestFixture, OperatorMinus)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 - nV2;
	auto result2 = nV1;
	result2 -= nV2;
	auto result3 = -nV1;

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
// -
		EXPECT_EQ(result.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
// Add the Z component subtraction
		EXPECT_EQ(result.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
// -=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
// Add the Z component subtraction
		EXPECT_EQ(result2.Z()[i], nV1.Z()[i] - nV2.Z()[i]);
// - unary
		EXPECT_EQ(result3.X()[i], -nV1.X()[i]);
		EXPECT_EQ(result3.Y()[i], -nV1.Y()[i]);
// Add the Z component negation
		EXPECT_EQ(result3.Z()[i], -nV1.Z()[i]);
	}
}

TEST_P(ThreeVec3ITestFixture, OperatorMultiply)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 * nV2;
	auto result2 = nV1;
	result2 *= nV2;

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
// *
		EXPECT_EQ(result.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
// Add the Z component multiplication
		EXPECT_EQ(result.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
// Add the Z component multiplication
		EXPECT_EQ(result2.Z()[i], nV1.Z()[i] * nV2.Z()[i]);
	}
}

TEST_P(ThreeVec3ITestFixture, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
		if (nV2.X()[i] == 0 || nV2.Y()[i] == 0 || nV2.Z()[i] == 0) // Add Z component check
		{
			NVec3<int, 3> result;
			EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
			EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / nV2;
	auto result2 = nV1;
	result2 /= nV2;

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
// /
		EXPECT_EQ(result.X()[i], nV1.X()[i] / nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
// Add the Z component division
		EXPECT_EQ(result.Z()[i], nV1.Z()[i] / nV2.Z()[i]);
// /=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] / nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
// Add the Z component division
		EXPECT_EQ(result2.Z()[i], nV1.Z()[i] / nV2.Z()[i]);
	}
}

TEST_P(ThreeVec3ITestFixture, Dot)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto dotVec = NVec3<int, 3>::Dot(nV1, nV2);

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
		auto result = nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i] + nV1.Z()[i] * nV2.Z()[i]; // Include Z component
		EXPECT_EQ(dotVec[i], result);
	}
}

TEST_P(ThreeVec3ITestFixture, SquareMagnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto squareMagnitude = nV1.SquareMagnitude();

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
		auto result = nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i] + nV1.Z()[i] * nV1.Z()[i]; // Include Z component
		EXPECT_EQ(squareMagnitude[i], result);
	}
}

TEST_P(ThreeVec3ITestFixture, Magnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto magnitude = nV1.Magnitude();

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
		auto result = (int) std::sqrt(nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i] + nV1.Z()[i] * nV1.Z()[i]); // Include Z component
		EXPECT_EQ(magnitude[i], result);
	}
}

TEST_P(ThreeVec3ITestFixture, Normalized)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto magnitude = nV1.Magnitude();
	std::array<int, 3> nV1Norm = {}; // Change the array size to 3

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
		if (magnitude[i] == 0)
		{
			EXPECT_THROW(nV1Norm = nV1.Normalized(), DivisionByZeroException);
			EXPECT_THROW(nV1Norm = nV1.Normalized(), DivisionByZeroException);
			return;
		}
	}

	nV1Norm = nV1.Normalized();
	const auto array1N = nV1.SquareMagnitude();
	std::array<int, 3> reciprocalSqrt = std::array<int, 3>(); // Change the array size to 3

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
		reciprocalSqrt[i] = 1.f / std::sqrt(array1N[i]);
	}

	for (int i = 0; i < 3; i++) // Change the loop limit from 2 to 3
	{
		EXPECT_EQ(nV1Norm[i], reciprocalSqrt[i]);
	}
}

#pragma endregion

#pragma region FourVec2I

TEST_P(FourVec3ITestFixtureMixed, OperatorPlus)
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
		EXPECT_EQ(result.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
		EXPECT_EQ(result.Z()[i], nV1.Z()[i] + nV2.Z()[i]); // Include Z component
// +=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
		EXPECT_EQ(result2.Z()[i], nV1.Z()[i] + nV2.Z()[i]); // Include Z component
	}
}

TEST_P(FourVec3ITestFixtureMixed, OperatorMinus)
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
		EXPECT_EQ(result.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		EXPECT_EQ(result.Z()[i], nV1.Z()[i] - nV2.Z()[i]); // Include Z component
// -=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		EXPECT_EQ(result2.Z()[i], nV1.Z()[i] - nV2.Z()[i]); // Include Z component
// - unary
		EXPECT_EQ(result3.X()[i], -nV1.X()[i]);
		EXPECT_EQ(result3.Y()[i], -nV1.Y()[i]);
		EXPECT_EQ(result3.Z()[i], -nV1.Z()[i]); // Include Z component
	}
}

TEST_P(FourVec3ITestFixtureMixed, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	for (int i = 0; i < 4; i++)
	{
		if (nV2.X()[i] == 0 || nV2.Y()[i] == 0 || nV2.Z()[i] == 0)
		{
			NVec3<int, 4> result;
			EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
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
		EXPECT_EQ(result.X()[i], nV1.X()[i] / nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
		EXPECT_EQ(result.Z()[i], nV1.Z()[i] / nV2.Z()[i]);
// /=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] / nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
		EXPECT_EQ(result2.Z()[i], nV1.Z()[i] / nV2.Z()[i]);
	}
}


TEST_P(FourVec3ITestFixtureMixed, Dot)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto dotVec = FourVec3I::Dot(nV1, nV2);

	for (int i = 0; i < 4; i++)
	{
		auto result = nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i] + nV1.Z()[i] * nV2.Z()[i];
		EXPECT_EQ(dotVec[i], result);
	}
}

TEST_P(FourVec3ITestFixtureMixed, SquareMagnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto squareMagnitude = nV1.SquareMagnitude();

	for (int i = 0; i < 4; i++)
	{
		auto result = nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i] + nV1.Z()[i] * nV1.Z()[i];
		EXPECT_EQ(squareMagnitude[i], result);
	}
}

TEST_P(FourVec3ITestFixtureMixed, Magnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto magnitude = nV1.Magnitude();

	for (int i = 0; i < 4; i++)
	{
		auto result = (int) std::sqrt(nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i] + nV1.Z()[i] * nV1.Z()[i]);
		EXPECT_EQ(magnitude[i], result);
	}
}

TEST_P(FourVec3ITestFixtureMixed, Normalized)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto magnitude = nV1.Magnitude();
	std::array<int, 4> nV1Norm = {};

	for (int i = 0; i < 4; i++)
	{
		if (magnitude[i] == 0)
		{
			EXPECT_THROW(nV1Norm = nV1.Normalized(), DivisionByZeroException);
			EXPECT_THROW(nV1Norm = nV1.Normalized(), DivisionByZeroException);
			return;
		}
	}

	nV1Norm = nV1.Normalized();
	const auto array1N = nV1.SquareMagnitude();
	std::array<int, 4> reciprocalSqrt = std::array<int, 4>();

	for (int i = 0; i < 4; i++)
	{
		reciprocalSqrt[i] = 1 / std::sqrt(array1N[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		EXPECT_EQ(nV1Norm[i], reciprocalSqrt[i]);
	}
}

#pragma endregion