#include "NVec2.h"

#include "gtest/gtest.h"

/**
 * @headerfile Test the NVec2.h classes and functions
 * @author Alexis
 */

using namespace Math;

struct TwoVec2FTestFixture : public ::testing::TestWithParam<std::pair<NVec2<float, 2>, NVec2<float, 2>>> {};
struct TwoVec2FTestFixtureScalar : public ::testing::TestWithParam<std::pair<NVec2<float, 2>, std::array<float, 2>>> {};

struct FourVec2FTestFixtureMixed : public ::testing::TestWithParam<std::pair<FourVec2F, FourVec2F>>
{
};
struct FourVec2FTestFixtureScalar : public ::testing::TestWithParam<std::pair<FourVec2F, std::array<float, 4>>>
{
};

struct TwoVec2ITestFixture : public ::testing::TestWithParam<std::pair<NVec2<int, 2>, NVec2<int, 2>>>{};
struct TwoVec2ITestFixtureScalar : public ::testing::TestWithParam<std::pair<NVec2<int, 2>, std::array<int, 2>>>{};

struct FourVec2ITestFixtureMixed : public ::testing::TestWithParam<std::pair<FourVec2I, FourVec2I>>
{
};
struct FourVec2ITestFixtureScalar : public ::testing::TestWithParam<std::pair<FourVec2I, std::array<int, 4>>>
{
};

#pragma region InstantiateParametrizedTests

INSTANTIATE_TEST_SUITE_P(NVec2, TwoVec2FTestFixture, testing::Values(
	std::make_pair(
		NVec2<float, 2>(std::array<Vec2F, 2>{ Vec2F{ 1.3f, 2.4f }, Vec2F{ 3.5f, 4.6f } }),
		NVec2<float, 2>(std::array<Vec2F, 2>{ Vec2F{ 10.3f, 2.4f }, Vec2F{ 32.5f, 4.6f } })
	),
    std::make_pair(
        NVec2<float, 2>(std::array<Vec2F, 2>{ Vec2F{ 1.3f, 2.4f }, Vec2F{ 3.5f, 4.6f } }),
        NVec2<float, 2>(std::array<Vec2F, 2>{ Vec2F{ 0, 2.4f }, Vec2F{ 32.5f, 4.6f } })
    )
));
INSTANTIATE_TEST_SUITE_P(NVec2, TwoVec2FTestFixtureScalar, testing::Values(
	std::make_pair(
		NVec2<float, 2>(std::array<Vec2F, 2>{ Vec2F{ 1.3f, 2.4f }, Vec2F{ 3.5f, 4.6f } }),
		std::array<float, 2>{ 10.3f, 2.4f }
	),
    std::make_pair(
        NVec2<float, 2>(std::array<Vec2F, 2>{ Vec2F{ 1.3f, 2.4f }, Vec2F{ 3.5f, 4.6f } }),
        std::array<float, 2>{ 0, 2.4f }
    )
));

INSTANTIATE_TEST_SUITE_P(NVec2, FourVec2FTestFixtureMixed, testing::Values(
	std::make_pair(
		FourVec2F(std::array<Vec2F, 4>{Vec2F(1.4f, 2.5f), Vec2F(3.6f, 4.7f), Vec2F(5.8f, 6.9f), Vec2F(7.10f, 8.11f)}),
		FourVec2F(std::array<Vec2F, 4>{Vec2F(5.f, 2.5f), Vec2F(32.6f, 4.7f), Vec2F(54.8f, 6.9f), Vec2F(76.10f, 8.11f)})
	),
    std::make_pair(
        FourVec2F(std::array<Vec2F, 4>{Vec2F(1.4f, 2.5f), Vec2F(3.6f, 4.7f), Vec2F(5.8f, 6.9f), Vec2F(7.10f, 8.11f)}),
        FourVec2F(std::array<Vec2F, 4>{Vec2F(0, 2.5f), Vec2F(32.6f, 4.7f), Vec2F(54.8f, 6.9f), Vec2F(76.10f, 8.11f)})
    )
));
INSTANTIATE_TEST_SUITE_P(NVec2, FourVec2FTestFixtureScalar, testing::Values(
	std::make_pair(
		FourVec2F(std::array<Vec2F, 4>{Vec2F(1.4f, 2.5f), Vec2F(3.6f, 4.7f), Vec2F(5.8f, 6.9f), Vec2F(7.10f, 8.11f)}),
		std::array<float, 4>{10.3f, 2.4f, 9.f, 4.6f}
	),
    std::make_pair(
        FourVec2F(std::array<Vec2F, 4>{Vec2F(1.4f, 2.5f), Vec2F(3.6f, 4.7f), Vec2F(5.8f, 6.9f), Vec2F(7.10f, 8.11f)}),
        std::array<float, 4>{0, 2.4f, 9.f, 4.6f}
    )
));

INSTANTIATE_TEST_SUITE_P(NVec2, TwoVec2ITestFixture, testing::Values(
	std::make_pair(
		NVec2<int, 2>(std::array<Vec2I, 2>{ Vec2I{ 1, 2 }, Vec2I{ 3, 4 } }),
		NVec2<int, 2>(std::array<Vec2I, 2>{ Vec2I{ 10, 2 }, Vec2I{ 32, 4 } })
	),
    std::make_pair(
        NVec2<int, 2>(std::array<Vec2I, 2>{ Vec2I{ 1, 2 }, Vec2I{ 3, 4 } }),
        NVec2<int, 2>(std::array<Vec2I, 2>{ Vec2I{ 0, 2 }, Vec2I{ 32, 4 } })
    )
));
INSTANTIATE_TEST_SUITE_P(NVec2, TwoVec2ITestFixtureScalar, testing::Values(
	std::make_pair(
		NVec2<int, 2>(std::array<Vec2I, 2>{ Vec2I{ 1, 2 }, Vec2I{ 3, 4 } }),
		std::array<int, 2>{ 10, 2 }
	),
    std::make_pair(
        NVec2<int, 2>(std::array<Vec2I, 2>{ Vec2I{ 1, 2 }, Vec2I{ 3, 4 } }),
        std::array<int, 2>{ 0, 2 }
    )
));

INSTANTIATE_TEST_SUITE_P(NVec2, FourVec2ITestFixtureMixed, testing::Values(
	std::make_pair(
		FourVec2I(std::array<Vec2I, 4>{Vec2I(1, 2), Vec2I(3, 4), Vec2I(5, 6), Vec2I(7, 8)}),
		FourVec2I(std::array<Vec2I, 4>{Vec2I(10, 2), Vec2I(0, 4), Vec2I(54, 6), Vec2I(76, 8)})
	),
    std::make_pair(
        FourVec2I(std::array<Vec2I, 4>{Vec2I(1, 2), Vec2I(3, 4), Vec2I(5, 6), Vec2I(7, 8)}),
        FourVec2I(std::array<Vec2I, 4>{Vec2I(0, 2), Vec2I(0, 4), Vec2I(54, 6), Vec2I(76, 8)})
    )
));

INSTANTIATE_TEST_SUITE_P(NVec2, FourVec2ITestFixtureScalar, testing::Values(
	std::make_pair(
		FourVec2I(std::array<Vec2I, 4>{Vec2I(1, 2), Vec2I(3, 4), Vec2I(5, 6), Vec2I(7, 8)}),
		std::array<int, 4>{0, 2, 32, 4}
	),
    std::make_pair(
        FourVec2I(std::array<Vec2I, 4>{Vec2I(1, 2), Vec2I(3, 4), Vec2I(5, 6), Vec2I(7, 8)}),
        std::array<int, 4>{0, 2, 0, 4}
    )
));

#pragma endregion

#pragma region TwoVec2F

TEST_P(TwoVec2FTestFixture, Constructor)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = NVec2<float, 2>(nV1);

	for (int i = 0; i < 2; i++)
	{
		EXPECT_EQ(nV1.X()[i], nV2.X()[i]);
		EXPECT_EQ(nV1.Y()[i], nV2.Y()[i]);
	}
}

TEST_P(TwoVec2FTestFixture, OperatorPlus)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 + nV2;
	auto result2 = nV1;
	result2 += nV2;

	for (int i = 0; i < 2; i++)
	{
		// +
		EXPECT_EQ(result.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
		// +=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
	}
}

TEST_P(TwoVec2FTestFixture, OperatorMinus)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 - nV2;
	auto result2 = nV1;
	result2 -= nV2;
	auto result3 = -nV1;

	for (int i = 0; i < 2; i++)
	{
		// -
		EXPECT_EQ(result.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		// -=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		// - unary
		EXPECT_EQ(result3.X()[i], -nV1.X()[i]);
		EXPECT_EQ(result3.Y()[i], -nV1.Y()[i]);
	}
}

TEST_P(TwoVec2FTestFixture, OperatorMultiply)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 * nV2;
	auto result2 = nV1;
	result2 *= nV2;

	for (int i = 0; i < 2; i++)
	{
		// *
		EXPECT_EQ(result.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
	}
}

TEST_P(TwoVec2FTestFixtureScalar, OperatorMultiply)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;

	auto result = nV1 * scalar;
	auto result2 = nV1;
	result2 *= scalar;

	for (int i = 0; i < 2; i++)
	{
		// *
		EXPECT_EQ(result.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * scalar[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * scalar[i]);
	}
}

TEST_P(TwoVec2FTestFixture, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;
	constexpr auto epsilon = 0.0001f;

	for (int i = 0; i < 2; i++)
	{
		if (nV2.X()[i] == 0 || nV2.Y()[i] == 0)
		{
            NVec2<float, 2> result;
			EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
			EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / nV2;
	auto result2 = nV1;
	result2 /= nV2;

	for (int i = 0; i < 2; i++)
	{
		// /
		EXPECT_NEAR(result.X()[i], nV1.X()[i] / nV2.X()[i], epsilon);
		EXPECT_NEAR(result.Y()[i], nV1.Y()[i] / nV2.Y()[i], epsilon);
		// /=
		EXPECT_NEAR(result2.X()[i], nV1.X()[i] / nV2.X()[i], epsilon);
		EXPECT_NEAR(result2.Y()[i], nV1.Y()[i] / nV2.Y()[i], epsilon);
	}
}

TEST_P(TwoVec2FTestFixtureScalar, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;
	constexpr auto epsilon = 0.0001f;

	for (int i = 0; i < 2; i++)
	{
		if (scalar[i] == 0)
		{
            NVec2<float, 2> result;
			EXPECT_THROW(result = nV1 / scalar, DivisionByZeroException);
			EXPECT_THROW(nV1 /= scalar, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / scalar;
	auto result2 = nV1;
	result2 /= scalar;

	for (int i = 0; i < 2; i++)
	{
		// /
		EXPECT_NEAR(result.X()[i], nV1.X()[i] / scalar[i], epsilon);
		EXPECT_NEAR(result.Y()[i], nV1.Y()[i] / scalar[i], epsilon);
		// /=
		EXPECT_NEAR(result2.X()[i], nV1.X()[i] / scalar[i], epsilon);
		EXPECT_NEAR(result2.Y()[i], nV1.Y()[i] / scalar[i], epsilon);
	}
}

TEST_P(TwoVec2FTestFixture, Dot)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = NVec2<float, 2>::Dot(nV1, nV2);

	for (int i = 0; i < 2; i++)
	{
		EXPECT_EQ(result[i], nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i]);
	}
}

TEST_P(TwoVec2FTestFixture, SquareMagnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto result = nV1.SquareMagnitude();

	for (int i = 0; i < 2; i++)
	{
		EXPECT_FLOAT_EQ(result[i], nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i]);
	}
}

TEST_P(TwoVec2FTestFixture, Magnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto result = nV1.Magnitude();

	for (int i = 0; i < 2; i++)
	{
		EXPECT_EQ(result[i], std::sqrt(nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i]));
	}
}

TEST_P(TwoVec2FTestFixture, Normalized)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto magnitude = nV1.Magnitude();
	constexpr auto epsilon = 0.001f;
	std::array<float, 2> nV1Norm = {};

	for (int i = 0; i < 2; i++)
	{
		if (magnitude[i] == 0)
		{
			EXPECT_THROW(nV1Norm = nV1.Normalized(), DivisionByZeroException);
			return;
		}
	}

	nV1Norm = nV1.Normalized();
	const auto array1N = nV1.SquareMagnitude();
	std::array<float, 2> reciprocalSqrt = std::array<float, 2>();

	for (int i = 0; i < 2; i++)
	{
		reciprocalSqrt[i] = 1 / std::sqrt(array1N[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		EXPECT_NEAR(nV1Norm[i], reciprocalSqrt[i], epsilon);
	}
}

#pragma endregion

#pragma region FourVec2F

TEST_P(FourVec2FTestFixtureMixed, OperatorPlus)
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
		// +=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
	}
}

TEST_P(FourVec2FTestFixtureMixed, OperatorMinus)
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
		// -=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		// - unary
		EXPECT_EQ(result3.X()[i], -nV1.X()[i]);
		EXPECT_EQ(result3.Y()[i], -nV1.Y()[i]);
	}
}

TEST_P(FourVec2FTestFixtureMixed, OperatorMultiply)
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
		EXPECT_EQ(result.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
	}
}

TEST_P(FourVec2FTestFixtureScalar, OperatorMultiply)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;

	auto result = nV1 * scalar;
	auto result2 = nV1;
	result2 *= scalar;

	for (int i = 0; i < 4; i++)
	{
		// *
		EXPECT_EQ(result.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * scalar[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * scalar[i]);
	}
}

TEST_P(FourVec2FTestFixtureMixed, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;
	constexpr auto epsilon = 0.0001f;

	for (int i = 0; i < 4; i++)
	{
		if (nV2.X()[i] == 0 || nV2.Y()[i] == 0)
		{
            NVec2<float, 4> result;
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
		// /=
		EXPECT_NEAR(result2.X()[i], nV1.X()[i] / nV2.X()[i], epsilon);
		EXPECT_NEAR(result2.Y()[i], nV1.Y()[i] / nV2.Y()[i], epsilon);
	}
}

TEST_P(FourVec2FTestFixtureScalar, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;
	constexpr auto epsilon = 0.0001f;

	for (int i = 0; i < 4; i++)
	{
		if (scalar[i] == 0)
		{
            NVec2<float, 4> result;
			EXPECT_THROW(result = nV1 / scalar, DivisionByZeroException);
			EXPECT_THROW(nV1 /= scalar, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / scalar;
	auto result2 = nV1;
	result2 /= scalar;

	for (int i = 0; i < 4; i++)
	{
		// /
		EXPECT_NEAR(result.X()[i], nV1.X()[i] / scalar[i], epsilon);
		EXPECT_NEAR(result.Y()[i], nV1.Y()[i] / scalar[i], epsilon);
		// /=
		EXPECT_NEAR(result2.X()[i], nV1.X()[i] / scalar[i], epsilon);
		EXPECT_NEAR(result2.Y()[i], nV1.Y()[i] / scalar[i], epsilon);
	}
}

TEST_P(FourVec2FTestFixtureMixed, Dot)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto dotVec = FourVec2F::Dot(nV1, nV2);

	for (int i = 0; i < 4; i++)
	{
		auto result = nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i];
		EXPECT_EQ(dotVec[i], result);
	}
}

TEST_P(FourVec2FTestFixtureMixed, SquareMagnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	constexpr auto epsilon = 0.0001f;

	auto squareMagnitude = nV1.SquareMagnitude();

	for (int i = 0; i < 4; i++)
	{
		auto result = nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i];
		EXPECT_NEAR(squareMagnitude[i], result, epsilon);
	}
}

TEST_P(FourVec2FTestFixtureMixed, Magnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	constexpr auto epsilon = 0.0001f;

	auto magnitude = nV1.Magnitude();

	for (int i = 0; i < 4; i++)
	{
		auto result = std::sqrt(nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i]);
		EXPECT_NEAR(magnitude[i], result, epsilon);
	}
}

TEST_P(FourVec2FTestFixtureMixed, Normalized)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto magnitude = nV1.Magnitude();
	constexpr auto epsilon = 0.001f;
	std::array<float, 4> nV1Norm = {};

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
	std::array<float, 4> reciprocalSqrt = std::array<float, 4>();

	for (int i = 0; i < 4; i++)
	{
		reciprocalSqrt[i] = 1 / std::sqrt(array1N[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		EXPECT_NEAR(nV1Norm[i], reciprocalSqrt[i], epsilon);
	}
}

#pragma endregion

#pragma region TwoVec2I

TEST_P(TwoVec2ITestFixture, Constructor)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = NVec2<int, 2>(nV1);

	for (int i = 0; i < 2; i++)
	{
		EXPECT_EQ(nV1.X()[i], nV2.X()[i]);
		EXPECT_EQ(nV1.Y()[i], nV2.Y()[i]);
	}
}

TEST_P(TwoVec2ITestFixture, OperatorPlus)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 + nV2;
	auto result2 = nV1;
	result2 += nV2;

	for (int i = 0; i < 2; i++)
	{
		// +
		EXPECT_EQ(result.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
		// +=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
	}
}

TEST_P(TwoVec2ITestFixture, OperatorMinus)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 - nV2;
	auto result2 = nV1;
	result2 -= nV2;
	auto result3 = -nV1;

	for (int i = 0; i < 2; i++)
	{
		// -
		EXPECT_EQ(result.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		// -=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		// - unary
		EXPECT_EQ(result3.X()[i], -nV1.X()[i]);
		EXPECT_EQ(result3.Y()[i], -nV1.Y()[i]);
	}
}

TEST_P(TwoVec2ITestFixture, OperatorMultiply)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto result = nV1 * nV2;
	auto result2 = nV1;
	result2 *= nV2;

	for (int i = 0; i < 2; i++)
	{
		// *
		EXPECT_EQ(result.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
	}
}

TEST_P(TwoVec2ITestFixtureScalar, OperatorMultiply)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;

	auto result = nV1 * scalar;
	auto result2 = nV1;
	result2 *= scalar;

	for (int i = 0; i < 2; i++)
	{
		// *
		EXPECT_EQ(result.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * scalar[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * scalar[i]);
	}
}

TEST_P(TwoVec2ITestFixture, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	for (int i = 0; i < 2; i++)
	{
		if (nV2.X()[i] == 0 || nV2.Y()[i] == 0)
		{
            NVec2<int, 2> result;
			EXPECT_THROW(result = nV1 / nV2, DivisionByZeroException);
			EXPECT_THROW(nV1 /= nV2, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / nV2;
	auto result2 = nV1;
	result2 /= nV2;

	for (int i = 0; i < 2; i++)
	{
		// /
		EXPECT_EQ(result.X()[i], nV1.X()[i] / nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
		// /=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] / nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
	}
}

TEST_P(TwoVec2ITestFixtureScalar, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;

	for (int i = 0; i < 2; i++)
	{
		if (scalar[i] == 0)
		{
            NVec2<int, 2> result;
			EXPECT_THROW(result = nV1 / scalar, DivisionByZeroException);
			EXPECT_THROW(nV1 /= scalar, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / scalar;
	auto result2 = nV1;
	result2 /= scalar;

	for (int i = 0; i < 2; i++)
	{
		// /
		EXPECT_EQ(result.X()[i], nV1.X()[i] / scalar[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] / scalar[i]);
		// /=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] / scalar[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] / scalar[i]);
	}
}

TEST_P(TwoVec2ITestFixture, Dot)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto dotVec = NVec2<int, 2>::Dot(nV1, nV2);

	for (int i = 0; i < 2; i++)
	{
		auto result = nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i];
		EXPECT_EQ(dotVec[i], result);
	}
}

TEST_P(TwoVec2ITestFixture, SquareMagnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto squareMagnitude = nV1.SquareMagnitude();

	for (int i = 0; i < 2; i++)
	{
		auto result = nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i];
		EXPECT_EQ(squareMagnitude[i], result);
	}
}

TEST_P(TwoVec2ITestFixture, Magnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto magnitude = nV1.Magnitude();

	for (int i = 0; i < 2; i++)
	{
		auto result = (int) std::sqrt(nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i]);
		EXPECT_EQ(magnitude[i], result);
	}
}

TEST_P(TwoVec2ITestFixture, Normalized)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto magnitude = nV1.Magnitude();
	std::array<int, 2> nV1Norm = {};

	for (int i = 0; i < 2; i++)
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
	std::array<int, 2> reciprocalSqrt = std::array<int, 2>();

	for (int i = 0; i < 2; i++)
	{
		reciprocalSqrt[i] = 1 / std::sqrt(array1N[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		EXPECT_EQ(nV1Norm[i], reciprocalSqrt[i]);
	}
}

#pragma endregion

#pragma region FourVec2I

TEST_P(FourVec2ITestFixtureMixed, OperatorPlus)
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
		// +=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] + nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] + nV2.Y()[i]);
	}
}

TEST_P(FourVec2ITestFixtureMixed, OperatorMinus)
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
		// -=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] - nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] - nV2.Y()[i]);
		// - unary
		EXPECT_EQ(result3.X()[i], -nV1.X()[i]);
		EXPECT_EQ(result3.Y()[i], -nV1.Y()[i]);
	}
}

TEST_P(FourVec2ITestFixtureMixed, OperatorMultiply)
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
		EXPECT_EQ(result.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * nV2.Y()[i]);
	}
}

TEST_P(FourVec2ITestFixtureMixed, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	for (int i = 0; i < 4; i++)
	{
		if (nV2.X()[i] == 0 || nV2.Y()[i] == 0)
		{
            NVec2<int, 4> result;
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
		// /=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] / nV2.X()[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] / nV2.Y()[i]);
	}
}

TEST_P(FourVec2ITestFixtureScalar, OperatorMultiplyScalar)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;

	auto result = nV1 * scalar;
	auto result2 = nV1;
	result2 *= scalar;

	for (int i = 0; i < 4; i++)
	{
		// *
		EXPECT_EQ(result.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * scalar[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * scalar[i]);
	}
}

TEST_P(FourVec2ITestFixtureScalar, OperatorMultiply)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;

	auto result = nV1 * scalar;
	auto result2 = nV1;
	result2 *= scalar;

	for (int i = 0; i < 4; i++)
	{
		// *
		EXPECT_EQ(result.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] * scalar[i]);
		// *=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] * scalar[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] * scalar[i]);
	}
}

TEST_P(FourVec2ITestFixtureScalar, OperatorDivideScalar)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;

	for (int i = 0; i < 4; i++)
	{
		if (scalar[i] == 0)
		{
            NVec2<int, 4> result;
			EXPECT_THROW(result = nV1 / scalar, DivisionByZeroException);
			EXPECT_THROW(nV1 /= scalar, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / scalar;
	auto result2 = nV1;
	result2 /= scalar;

	for (int i = 0; i < 4; i++)
	{
		// /
		EXPECT_EQ(result.X()[i], nV1.X()[i] / scalar[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] / scalar[i]);
		// /=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] / scalar[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] / scalar[i]);
	}
}

TEST_P(FourVec2ITestFixtureScalar, OperatorDivide)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto scalar = pair.second;

	for (int i = 0; i < 4; i++)
	{
		if (scalar[i] == 0)
		{
            NVec2<int, 4> result;
			EXPECT_THROW(result = nV1 / scalar, DivisionByZeroException);
			EXPECT_THROW(nV1 /= scalar, DivisionByZeroException);
			return;
		}
	}

	auto result = nV1 / scalar;
	auto result2 = nV1;
	result2 /= scalar;

	for (int i = 0; i < 4; i++)
	{
		// /
		EXPECT_EQ(result.X()[i], nV1.X()[i] / scalar[i]);
		EXPECT_EQ(result.Y()[i], nV1.Y()[i] / scalar[i]);
		// /=
		EXPECT_EQ(result2.X()[i], nV1.X()[i] / scalar[i]);
		EXPECT_EQ(result2.Y()[i], nV1.Y()[i] / scalar[i]);
	}
}

TEST_P(FourVec2ITestFixtureMixed, Dot)
{
	auto pair = GetParam();
	auto nV1 = pair.first;
	auto nV2 = pair.second;

	auto dotVec = FourVec2I::Dot(nV1, nV2);

	for (int i = 0; i < 4; i++)
	{
		auto result = nV1.X()[i] * nV2.X()[i] + nV1.Y()[i] * nV2.Y()[i];
		EXPECT_EQ(dotVec[i], result);
	}
}

TEST_P(FourVec2ITestFixtureMixed, SquareMagnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto squareMagnitude = nV1.SquareMagnitude();

	for (int i = 0; i < 4; i++)
	{
		auto result = nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i];
		EXPECT_EQ(squareMagnitude[i], result);
	}
}

TEST_P(FourVec2ITestFixtureMixed, Magnitude)
{
	auto pair = GetParam();
	auto nV1 = pair.first;

	auto magnitude = nV1.Magnitude();

	for (int i = 0; i < 4; i++)
	{
		auto result = (int) std::sqrt(nV1.X()[i] * nV1.X()[i] + nV1.Y()[i] * nV1.Y()[i]);
		EXPECT_EQ(magnitude[i], result);
	}
}

TEST_P(FourVec2ITestFixtureMixed, Normalized)
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