/**
 * @headerfile Test the Vec2.h classes and functions
 * @author Alexis
 */

#include "Vec2.h"
#include "Random.h"

#include "gtest/gtest.h"


using namespace Math;

constexpr int ValuesSize = 30;

enum numberType
{
	Positive, Negative, Mixed, Time
};

template <typename T>
T* GenerateValues(numberType type, bool reverseOrder = false)
{
	auto* list = new T[ValuesSize];

	for (int i = 1; i < ValuesSize + 1; i++)
	{
		T number = 0;
		int j = reverseOrder ? ValuesSize - i + 1 : i;

		switch (type)
		{
			case Positive: number = j; break;
			case Negative: number = -j; break;
			case Mixed: number = j % 2 == 0 ? j : -j; break;
			case Time: number = static_cast<float>(j) / static_cast<float>(ValuesSize); break;
		}

		list[i - 1] = number;
	}

	return list;
}

template <typename T>
Vec2<T>* GenerateVectors(numberType type, bool reverseOrder = false)
{
	auto* list = new Vec2<T>[ValuesSize];
	auto* values = GenerateValues<T>(type);
	auto* values2 = GenerateValues<T>(type, true);

	for (int i = 0; i < ValuesSize; i++)
	{
		const auto index = reverseOrder ? ValuesSize - i - 1 : i;

		list[i] = Vec2<T>(values[index], values2[index]);
	}

	delete[] values;
	delete[] values2;

	return list;
}

struct FloatTestFixtureMixed : public ::testing::TestWithParam<float*> {};
struct IntTestFixtureMixed : public ::testing::TestWithParam<int*> {};
// Vec2F
struct Vec2FTestFixtureMixedPair : public ::testing::TestWithParam<std::pair<Vec2F*, Vec2F*>> {};
struct Vec2FTestFixtureVecAndScalar : public ::testing::TestWithParam<std::pair<Vec2F*, float*>> {};
struct Vec2FTestFixtureMixedPairWithScalar : public ::testing::TestWithParam<std::pair<std::pair<Vec2F*, Vec2F*>, float*>> {};
struct Vec2FTestFixtureMixedVec : public ::testing::TestWithParam<Vec2F*> {};
struct Vec2FTestFixtureMixedPairWithTime : public ::testing::TestWithParam<std::pair<std::pair<Vec2F*, Vec2F*>, float*>> {};
// Vec2I
struct Vec2ITestFixtureMixedPair : public ::testing::TestWithParam<std::pair<Vec2I*, Vec2I*>> {};
struct Vec2ITestFixtureVecAndScalar : public ::testing::TestWithParam<std::pair<Vec2I*, int*>> {};
struct Vec2ITestFixtureMixedPairWithScalar : public ::testing::TestWithParam<std::pair<std::pair<Vec2I*, Vec2I*>, int*>> {};
struct Vec2ITestFixtureMixedVec : public ::testing::TestWithParam<Vec2I*> {};
struct Vec2ITestFixtureMixedPairWithTime : public ::testing::TestWithParam<std::pair<std::pair<Vec2I*, Vec2I*>, float*>> {};

INSTANTIATE_TEST_SUITE_P(Float, FloatTestFixtureMixed, testing::Values(GenerateValues<float>(Mixed)));
INSTANTIATE_TEST_SUITE_P(Int, IntTestFixtureMixed, testing::Values(GenerateValues<int>(Mixed)));

INSTANTIATE_TEST_SUITE_P(Vec2F, Vec2FTestFixtureMixedPair, testing::Values(std::pair(GenerateVectors<float>(Mixed), GenerateVectors<float>(Mixed, true))));
INSTANTIATE_TEST_SUITE_P(Vec2F, Vec2FTestFixtureVecAndScalar, testing::Values(std::pair(GenerateVectors<float>(Mixed), GenerateValues<float>(Mixed))));
INSTANTIATE_TEST_SUITE_P(Vec2F, Vec2FTestFixtureMixedPairWithScalar, testing::Values(std::pair(std::pair(GenerateVectors<float>(Mixed), GenerateVectors<float>(Mixed, true)), GenerateValues<float>(Mixed))));
INSTANTIATE_TEST_SUITE_P(Vec2F, Vec2FTestFixtureMixedVec, testing::Values(GenerateVectors<float>(Mixed)));
INSTANTIATE_TEST_SUITE_P(Vec2F, Vec2FTestFixtureMixedPairWithTime, testing::Values(std::pair(std::pair(GenerateVectors<float>(Mixed), GenerateVectors<float>(Mixed, true)), GenerateValues<float>(Time))));

INSTANTIATE_TEST_SUITE_P(Vec2I, Vec2ITestFixtureMixedPair, testing::Values(std::pair(GenerateVectors<int>(Mixed),GenerateVectors<int>(Mixed, true))));
INSTANTIATE_TEST_SUITE_P(Vec2I, Vec2ITestFixtureVecAndScalar, testing::Values(std::pair(GenerateVectors<int>(Mixed), GenerateValues<int>(Mixed))));
INSTANTIATE_TEST_SUITE_P(Vec2I, Vec2ITestFixtureMixedPairWithScalar, testing::Values(std::pair(std::pair(GenerateVectors<int>(Mixed), GenerateVectors<int>(Mixed, true)), GenerateValues<int>(Mixed))));
INSTANTIATE_TEST_SUITE_P(Vec2I, Vec2ITestFixtureMixedVec, testing::Values(GenerateVectors<int>(Mixed)));
INSTANTIATE_TEST_SUITE_P(Vec2I, Vec2ITestFixtureMixedPairWithTime, testing::Values(std::pair(std::pair(GenerateVectors<int>(Mixed), GenerateVectors<int>(Mixed, true)), GenerateValues<float>(Time))));

TEST(Vec2, StaticVariables)
{
    EXPECT_EQ(Vec2I::Zero(), Vec2I(0, 0));
    EXPECT_EQ(Vec2I::One(), Vec2I(1, 1));
    EXPECT_EQ(Vec2I::Up(), Vec2I(0, 1));
    EXPECT_EQ(Vec2I::Down(), Vec2I(0, -1));
    EXPECT_EQ(Vec2I::Left(), Vec2I(-1, 0));
    EXPECT_EQ(Vec2I::Right(), Vec2I(1, 0));

    EXPECT_EQ(Vec2F::Zero(), Vec2F(0, 0));
    EXPECT_EQ(Vec2F::One(), Vec2F(1, 1));
    EXPECT_EQ(Vec2F::Up(), Vec2F(0, 1));
    EXPECT_EQ(Vec2F::Down(), Vec2F(0, -1));
    EXPECT_EQ(Vec2F::Left(), Vec2F(-1, 0));
    EXPECT_EQ(Vec2F::Right(), Vec2F(1, 0));
}

#pragma region Vec2i

TEST_P(IntTestFixtureMixed, Constructor)
{
	auto* values = GetParam();

	for (int i = 0; i < ValuesSize; i++)
	{
		Vec2I vec2i(values[i], values[i]);

		EXPECT_EQ(vec2i.X, values[i]);
		EXPECT_EQ(vec2i.Y, values[i]);
	}
}

TEST_P(Vec2ITestFixtureMixedPair, OperatorPlus)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* additives = pair.second;

	for (int i = 0; i < ValuesSize; i++)
	{
		Vec2I value = values[i];
		Vec2I additive = additives[i];
		Vec2I result = value;

		result += additive;

		// += operator
		EXPECT_EQ(result.X, value.X + additive.X);
		EXPECT_EQ(result.Y, value.Y + additive.Y);
		// + operator
		EXPECT_EQ((value + additive).X, value.X + additive.X);
		EXPECT_EQ((value + additive).Y, value.Y + additive.Y);
	}
}

TEST_P(Vec2ITestFixtureMixedPair, OperatorMinus)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* additives = pair.second;

	for (int i = 0; i < ValuesSize; i++)
	{
		auto value = values[i];
		auto additive = additives[i];
		auto result = value;

		result -= additive;

		// -= operator
		EXPECT_EQ(result.X, value.X - additive.X);
		EXPECT_EQ(result.Y, value.Y - additive.Y);
		// - operator
		EXPECT_EQ((value - additive).X, value.X - additive.X);
		EXPECT_EQ((value - additive).Y, value.Y - additive.Y);
		// - unary operator
		EXPECT_EQ((-value).X, -value.X);
		EXPECT_EQ((-value).Y, -value.Y);
	}
}

TEST_P(Vec2ITestFixtureMixedPairWithScalar, OperatorMultiply)
{
	auto pair = GetParam();
	auto* values = pair.first.first;
	auto* multipliers = pair.first.second;
	auto* scalars = pair.second;

	for (int i = 0; i < ValuesSize; i++)
	{
		auto value = values[i];
		auto multiplier = multipliers[i];
		auto scalar = scalars[i];
		auto result = value;
		auto resultScalar = value;

		result *= multiplier;
		resultScalar *= scalar;

		// *= operator with Vec2
		EXPECT_EQ(result.X, value.X * multiplier.X);
		EXPECT_EQ(result.Y, value.Y * multiplier.Y);
		// * operator with Vec2
		EXPECT_EQ((value * multiplier).X, value.X * multiplier.X);
		EXPECT_EQ((value * multiplier).Y, value.Y * multiplier.Y);
		// *= operator with scalar
		EXPECT_EQ(resultScalar.X, value.X * scalar);
		EXPECT_EQ(resultScalar.Y, value.Y * scalar);
		// * operator with scalar
		EXPECT_EQ((value * scalar).X, value.X * scalar);
		EXPECT_EQ((value * scalar).Y, value.Y * scalar);
		// friend * operator with scalar
		EXPECT_EQ((scalar * value).X, scalar * value.X);
		EXPECT_EQ((scalar * value).Y, scalar * value.Y);
	}
}

TEST_P(Vec2ITestFixtureMixedPairWithScalar, OperatorDivide)
{
	const auto pairs = GetParam();
	auto* values = pairs.first.first;
	const auto* dividers = pairs.first.second;
	const auto* scalars = pairs.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		const auto value = values[i];
		const auto divisor = dividers[i];
		const auto scalar = scalars[i];
		auto result = value;
		auto resultScalar = value;

		if (divisor.X == 0 || divisor.Y == 0)
		{
			Vec2I res;
			EXPECT_THROW(res = result / divisor, DivisionByZeroException);
			EXPECT_THROW(result /= divisor, DivisionByZeroException);
			continue;
		}

		if (scalar == 0)
		{
			Vec2I res;
			EXPECT_THROW(res = resultScalar / scalar, DivisionByZeroException);
			EXPECT_THROW(resultScalar /= scalar, DivisionByZeroException);
			continue;
		}

		result /= divisor;
		resultScalar /= scalar;

		// /= operator with Vec2
		EXPECT_EQ(result.X, value.X / divisor.X);
		EXPECT_EQ(result.Y, value.Y / divisor.Y);
		// / operator with Vec2
		EXPECT_EQ((value / divisor).X, value.X / divisor.X);
		EXPECT_EQ((value / divisor).Y, value.Y / divisor.Y);
		// /= operator with scalar
		EXPECT_EQ(resultScalar.X, value.X / scalar);
		EXPECT_EQ(resultScalar.Y, value.Y / scalar);
		// / operator with scalar
		EXPECT_EQ((value / scalar).X, value.X / scalar);
		EXPECT_EQ((value / scalar).Y, value.Y / scalar);
	}
}

TEST_P(Vec2ITestFixtureMixedPair, OperatorEqual)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		EXPECT_EQ(values[i].X == values2[i].X && values[i].Y == values2[i].Y, values[i] == values2[i]);
		EXPECT_EQ(values[i].X != values2[i].X || values[i].Y != values2[i].Y, values[i] != values2[i]);
	}
}

TEST_P(Vec2ITestFixtureMixedVec, OperatorIndex)
{
	auto* values = GetParam();

	for (size_t i = 0; i < ValuesSize; i++)
	{
		Vec2I value = values[i];

		EXPECT_EQ(value[0], values[i].X);
		EXPECT_EQ(value[1], values[i].Y);
	}

	int res;
	EXPECT_THROW(res = values[0][2], OutOfRangeException);
}

TEST_P(Vec2ITestFixtureMixedPair, Dot)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		EXPECT_EQ(values[i].X * values2[i].X + values[i].Y * values2[i].Y, values[i].Dot(values2[i]));
	}
}

TEST_P(Vec2ITestFixtureMixedPair, Length)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto length = std::sqrt(values[i].X * values[i].X + values[i].Y * values[i].Y);
		EXPECT_EQ(static_cast<int>(length), values[i].Length());
	}
}

TEST_P(Vec2ITestFixtureMixedVec, Normalized)
{
	auto* values = GetParam();

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto length = static_cast<int>(std::sqrt(values[i].X * values[i].X + values[i].Y * values[i].Y));

		if (length == 0)
		{
			Vec2I norm;
			EXPECT_THROW(norm = values[i].Normalized(), DivisionByZeroException);
			continue;
		}

		auto normalized = Vec2I(values[i].X / length, values[i].Y / length);

		EXPECT_EQ(normalized.X, values[i].Normalized().X);
		EXPECT_EQ(normalized.Y, values[i].Normalized().Y);
	}

	// Test divisions by 0
	Vec2I zero(0, 0);
	Vec2I norm;

	EXPECT_THROW(norm = zero.Normalized(), DivisionByZeroException);
}

TEST_P(Vec2ITestFixtureMixedPair, IsPerpendicular)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		EXPECT_EQ(values[i].Dot(values2[i]) == 0, values[i].IsPerpendicular(values2[i]));
	}
}

TEST_P(Vec2ITestFixtureMixedPair, IsParallel)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		const auto result = values[i].X * values2[i].Y - values[i].Y * values2[i].X;
		EXPECT_EQ(result == 0, values[i].IsParallel(values2[i]));
	}
}

TEST_P(Vec2ITestFixtureMixedPair, Project)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		Vec2I vecUnit;

		try
		{
			vecUnit = values2[i].Normalized();
		}
		catch (const DivisionByZeroException& e)
		{
			Vec2I projected;
			EXPECT_THROW(projected = values[i].Project(values2[i]), DivisionByZeroException);
			continue;
		}
		catch (...)
		{
			FAIL();
		}

		auto projected = values[i].Dot(vecUnit) * vecUnit;

		EXPECT_EQ(projected, values[i].Project(values2[i]));
	}
}

TEST_P(Vec2ITestFixtureMixedPair, Reflect)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		Vec2I currentVec = values[i];
		Vec2I normalizedVec;

		try
		{
			normalizedVec = values2[i].Normalized();
		}
		catch (const DivisionByZeroException& e)
		{
			Vec2I reflected;
			EXPECT_THROW(reflected = currentVec.Reflect(values2[i]), DivisionByZeroException);
			continue;
		}
		catch (...)
		{
			FAIL();
		}

		Vec2I reflected = currentVec - 2 * (currentVec - normalizedVec) * normalizedVec;

		EXPECT_EQ(reflected, currentVec.Reflect(values2[i]));
	}
}

TEST_P(Vec2ITestFixtureMixedPair, Angle)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto vecAf = Vec2I(values[i].X, values[i].Y);
		auto vecBf = Vec2I(values2[i].X, values2[i].Y);

		auto angle = std::acos(vecAf.Dot(vecBf) / (vecAf.Length() * vecBf.Length()));

		EXPECT_EQ(static_cast<Radian>(angle), Vec2I::Angle(values[i], values2[i]));
	}
}

TEST_P(Vec2ITestFixtureMixedPairWithTime, Lerp)
{
	auto pair = GetParam();
	auto* values = pair.first.first;
	auto* values2 = pair.first.second;
	auto* times = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto vecAf = Vec2I(values[i].X, values[i].Y);
		auto vecBf = Vec2I(values2[i].X, values2[i].Y);

		Vec2I lerp = vecAf + (vecBf - vecAf) * times[i];

		EXPECT_EQ(lerp, Vec2I::Lerp(values[i], values2[i], times[i]));
	}
}

TEST_P(Vec2ITestFixtureMixedPairWithTime, Slerp)
{
	auto pair = GetParam();
	auto* values = pair.first.first;
	auto* values2 = pair.first.second;
	auto* times = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto vecAf = Vec2I(values[i].X, values[i].Y);
		auto vecBf = Vec2I(values2[i].X, values2[i].Y);
		Radian angleBetween;

		try
		{
			angleBetween = Vec2I::Angle(values[i], values2[i]);
		}
		catch (const DivisionByZeroException& e)
		{
			Vec2I slerp;
			EXPECT_THROW(slerp = Vec2I::Slerp(values[i], values2[i], times[i]), DivisionByZeroException);
			continue;
		}

		float sinAngle = Sin(angleBetween);
		float sinAngleT = Sin(times[i] * angleBetween);
		float sinAngle1T = Sin((1 - times[i]) * angleBetween);

		if (sinAngle == 0)
		{
			Vec2I slerp;
			EXPECT_THROW(slerp = Vec2I::Slerp(values[i], values2[i], times[i]), DivisionByZeroException);
			continue;
		}

		float tOnAngle = sinAngleT / sinAngle;
		float oneMinusTOnAngle = sinAngle1T / sinAngle;

		Vec2I slerp = vecAf * oneMinusTOnAngle + vecBf * tOnAngle;

		EXPECT_EQ(slerp, Vec2I::Slerp(values[i], values2[i], times[i]));
	}
}

TEST_P(Vec2ITestFixtureMixedPair, Distance)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto distance = static_cast<int>(std::sqrt(std::pow(values[i].X - values2[i].X, 2) + std::pow(values[i].Y - values2[i].Y, 2)));

		EXPECT_EQ(distance, Vec2I::Distance(values[i], values2[i]));
	}
}

TEST_P(Vec2ITestFixtureVecAndScalar, Rotate)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* scalars = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto vecAf = Vec2I(values[i].X, values[i].Y);
		auto angle = Radian(scalars[i]);

		float cos = Cos(angle);
		float sin = Sin(angle);

		int x = values[i].X * cos - values[i].Y * sin;
		int y = values[i].X * sin + values[i].Y * cos;

		Vec2I rotated(x, y);
		Vec2I result = values[i];

		result.Rotate(static_cast<Radian>(angle));

		EXPECT_EQ(rotated, result);
	}
}

#pragma endregion

#pragma region Vec2f

TEST_P(FloatTestFixtureMixed, Constructor)
{
	auto* values = GetParam();

	for (int i = 0; i < ValuesSize; i++)
	{
		Vec2F vec2f(values[i], values[i]);

		EXPECT_FLOAT_EQ(vec2f.X, values[i]);
		EXPECT_FLOAT_EQ(vec2f.Y, values[i]);
	}
}

TEST_P(Vec2FTestFixtureMixedPair, OperatorPlus)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* additives = pair.second;

	for (int i = 0; i < ValuesSize; i++)
	{
		Vec2F value = values[i];
		Vec2F additive = additives[i];
		Vec2F result = value;

		result += additive;

		// += operator
		EXPECT_FLOAT_EQ(result.X, value.X + additive.X);
		EXPECT_FLOAT_EQ(result.Y, value.Y + additive.Y);
		// + operator
		EXPECT_FLOAT_EQ((value + additive).X, value.X + additive.X);
		EXPECT_FLOAT_EQ((value + additive).Y, value.Y + additive.Y);
	}
}

TEST_P(Vec2FTestFixtureMixedPair, OperatorMinus)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* additives = pair.second;

	for (int i = 0; i < ValuesSize; i++)
	{
		Vec2F value = values[i];
		Vec2F additive = additives[i];
		Vec2F result = value;

		result -= additive;

		// -= operator
		EXPECT_FLOAT_EQ(result.X, value.X - additive.X);
		EXPECT_FLOAT_EQ(result.Y, value.Y - additive.Y);
		// - operator
		EXPECT_FLOAT_EQ((value - additive).X, value.X - additive.X);
		EXPECT_FLOAT_EQ((value - additive).Y, value.Y - additive.Y);
		// - unary operator
		EXPECT_FLOAT_EQ((-value).X, -value.X);
		EXPECT_FLOAT_EQ((-value).Y, -value.Y);
	}
}

TEST_P(Vec2FTestFixtureMixedPairWithScalar, OperatorMultiply)
{
	auto pair = GetParam();
	auto* values = pair.first.first;
	auto* multipliers = pair.first.second;
	auto* scalars = pair.second;

	for (int i = 0; i < ValuesSize; i++)
	{
		Vec2F value = values[i];
		Vec2F multiplier = multipliers[i];
		float scalar = scalars[i];
		Vec2F result = value;
		Vec2F resultScalar = value;

		result *= multiplier;
		resultScalar *= scalar;

		// *= operator with Vec2
		EXPECT_FLOAT_EQ(result.X, value.X * multiplier.X);
		EXPECT_FLOAT_EQ(result.Y, value.Y * multiplier.Y);
		// * operator with Vec2
		EXPECT_FLOAT_EQ((value * multiplier).X, value.X * multiplier.X);
		EXPECT_FLOAT_EQ((value * multiplier).Y, value.Y * multiplier.Y);
		// *= operator with scalar
		EXPECT_FLOAT_EQ(resultScalar.X, value.X * scalar);
		EXPECT_FLOAT_EQ(resultScalar.Y, value.Y * scalar);
		// * operator with scalar
		EXPECT_FLOAT_EQ((value * scalar).X, value.X * scalar);
		EXPECT_FLOAT_EQ((value * scalar).Y, value.Y * scalar);
		// friend * operator with scalar
		EXPECT_FLOAT_EQ((scalar * value).X, scalar * value.X);
		EXPECT_FLOAT_EQ((scalar * value).Y, scalar * value.Y);
	}
}

TEST_P(Vec2FTestFixtureMixedPairWithScalar, OperatorDivide)
{
	auto pair = GetParam();
	auto* values = pair.first.first;
	auto* dividers = pair.first.second;
	auto* scalars = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		Vec2F value = values[i];
		Vec2F divisor = dividers[i];
		float scalar = scalars[i];
		Vec2F result = value;
		Vec2F resultScalar = value;

		if (divisor.X == 0 || divisor.Y == 0)
		{
			Vec2F res;
			EXPECT_THROW(res = result / divisor, DivisionByZeroException);
			EXPECT_THROW(result /= divisor, DivisionByZeroException);
			continue;
		}

		if (scalar == 0)
		{
			Vec2F res;
			EXPECT_THROW(res = resultScalar / scalar, DivisionByZeroException);
			EXPECT_THROW(resultScalar /= scalar, DivisionByZeroException);
			continue;
		}

		result /= divisor;
		resultScalar /= scalar;

		// /= operator with Vec2
		EXPECT_FLOAT_EQ(result.X, value.X / divisor.X);
		EXPECT_FLOAT_EQ(result.Y, value.Y / divisor.Y);
		// / operator with Vec2
		EXPECT_FLOAT_EQ((value / divisor).X, value.X / divisor.X);
		EXPECT_FLOAT_EQ((value / divisor).Y, value.Y / divisor.Y);
		// /= operator with scalar
		EXPECT_FLOAT_EQ(resultScalar.X, value.X / scalar);
		EXPECT_FLOAT_EQ(resultScalar.Y, value.Y / scalar);
		// / operator with scalar
		EXPECT_FLOAT_EQ((value / scalar).X, value.X / scalar);
		EXPECT_FLOAT_EQ((value / scalar).Y, value.Y / scalar);
	}
}

TEST_P(Vec2FTestFixtureMixedPair, OperatorEqual)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		EXPECT_EQ(values[i].X == values2[i].X && values[i].Y == values2[i].Y, values[i] == values2[i]);
		EXPECT_EQ(values[i].X != values2[i].X || values[i].Y != values2[i].Y, values[i] != values2[i]);
	}
}

TEST_P(Vec2FTestFixtureMixedVec, OperatorIndex)
{
	auto* values = GetParam();

	for (size_t i = 0; i < ValuesSize; i++)
	{
		Vec2F value = values[i];

		EXPECT_FLOAT_EQ(value[0], values[i].X);
		EXPECT_FLOAT_EQ(value[1], values[i].Y);
	}

	float res;
	EXPECT_THROW(res = values[0][2], OutOfRangeException);
}

TEST_P(Vec2FTestFixtureMixedPair, Dot)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		EXPECT_FLOAT_EQ(values[i].X * values2[i].X + values[i].Y * values2[i].Y, values[i].Dot(values2[i]));
	}
}

TEST_P(Vec2FTestFixtureMixedPair, Length)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto length = std::sqrt(values[i].X * values[i].X + values[i].Y * values[i].Y);
		EXPECT_FLOAT_EQ(length, values[i].Length());
	}
}

TEST_P(Vec2FTestFixtureMixedPair, SquareLength)
{
    auto pair = GetParam();
    auto* values = pair.first;
    auto* values2 = pair.second;

    for (size_t i = 0; i < ValuesSize; i++)
    {
        auto length = values[i].X * values[i].X + values[i].Y * values[i].Y;
        EXPECT_FLOAT_EQ(length, values[i].SquareLength());
    }
}

TEST_P(Vec2FTestFixtureMixedVec, Normalized)
{
	auto* values = GetParam();

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto length = std::sqrt(values[i].X * values[i].X + values[i].Y * values[i].Y);

		if (length == 0)
		{
			Vec2F norm;
			EXPECT_THROW(norm = values[i].Normalized(), DivisionByZeroException);
			continue;
		}

		auto normalized = Vec2F(values[i].X / length, values[i].Y / length);

		EXPECT_FLOAT_EQ(normalized.X, values[i].Normalized().X);
		EXPECT_FLOAT_EQ(normalized.Y, values[i].Normalized().Y);
	}

	// Test divisions by 0
	Vec2F zero(0, 0);
	Vec2F norm;

	EXPECT_THROW(norm = zero.Normalized(), DivisionByZeroException);
}

TEST_P(Vec2FTestFixtureMixedPair, IsPerpendicular)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;
	const auto epsilon = 0.0001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto dot = values[i].Dot(values2[i]);

		EXPECT_EQ(std::abs(dot) < epsilon, values[i].IsPerpendicular(values2[i]));
	}
}

TEST_P(Vec2FTestFixtureMixedPair, IsParallel)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;
	const auto epsilon = 0.0001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		const auto result = values[i].X * values2[i].Y - values[i].Y * values2[i].X;

		EXPECT_EQ(std::abs(result) < epsilon, values[i].IsParallel(values2[i]));
	}
}

TEST_P(Vec2FTestFixtureMixedPair, Project)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;
	const auto epsilon = 0.0001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		Vec2F vecUnit;

		try
		{
			vecUnit = values2[i].Normalized();
		}
		catch (const DivisionByZeroException& e)
		{
			Vec2F projected;
			EXPECT_THROW(projected = values[i].Project(values2[i]), DivisionByZeroException);
			continue;
		}
		catch (...)
		{
			FAIL();
		}

		auto projected = values[i].Dot(vecUnit) * vecUnit;

		EXPECT_NEAR(projected.X, values[i].Project(values2[i]).X, epsilon);
		EXPECT_NEAR(projected.Y, values[i].Project(values2[i]).Y, epsilon);
	}
}

TEST_P(Vec2FTestFixtureMixedPair, Reflect)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;
	const auto epsilon = 0.0001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		Vec2F currentVec = values[i];
		Vec2F normalizedVec;

		try
		{
			normalizedVec = values2[i].Normalized();
		}
		catch (const DivisionByZeroException& e)
		{
			Vec2F reflected;
			EXPECT_THROW(reflected = currentVec.Reflect(values2[i]), DivisionByZeroException);
			continue;
		}
		catch (...)
		{
			FAIL();
		}

		Vec2F reflected = currentVec - 2 * (currentVec - normalizedVec) * normalizedVec;

		EXPECT_NEAR(reflected.X, currentVec.Reflect(values2[i]).X, epsilon);
		EXPECT_NEAR(reflected.Y, currentVec.Reflect(values2[i]).Y, epsilon);
	}
}

TEST_P(Vec2FTestFixtureMixedPair, Angle)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;
	const auto epsilon = 0.0001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto vecAf = Vec2F(values[i].X, values[i].Y);
		auto vecBf = Vec2F(values2[i].X, values2[i].Y);
		auto divisor = vecAf.Length() * vecBf.Length();

		if (divisor == 0)
		{
			Radian angle;
			EXPECT_THROW(angle = Vec2F::Angle(values[i], values2[i]), DivisionByZeroException);
			continue;
		}

		float angle = std::acos(vecAf.Dot(vecBf) / (vecAf.Length() * vecBf.Length()));

		if (std::isnan(angle))
		{
			Radian angle2;
			EXPECT_THROW(angle2 = Vec2F::Angle(values[i], values2[i]), NaNException);
			continue;
		}

		EXPECT_NEAR(static_cast<float>(Radian(angle)), static_cast<float>(Vec2F::Angle(values[i], values2[i])), epsilon);
	}
}

TEST_P(Vec2FTestFixtureMixedPairWithTime, Lerp)
{
	auto pair = GetParam();
	auto* values = pair.first.first;
	auto* values2 = pair.first.second;
	auto* times = pair.second;
	const auto epsilon = 0.0001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto vecAf = Vec2F(values[i].X, values[i].Y);
		auto vecBf = Vec2F(values2[i].X, values2[i].Y);

		Vec2F lerp = vecAf + (vecBf - vecAf) * times[i];

		EXPECT_NEAR(lerp.X, Vec2F::Lerp(values[i], values2[i], times[i]).X, epsilon);
		EXPECT_NEAR(lerp.Y, Vec2F::Lerp(values[i], values2[i], times[i]).Y, epsilon);
	}
}

TEST_P(Vec2FTestFixtureMixedPairWithTime, Slerp)
{
	auto pair = GetParam();
	auto* values = pair.first.first;
	auto* values2 = pair.first.second;
	auto* times = pair.second;
	const auto epsilon = 0.0001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto vecAf = Vec2F(values[i].X, values[i].Y);
		auto vecBf = Vec2F(values2[i].X, values2[i].Y);
		Radian angleBetween;

		try
		{
			angleBetween = Vec2F::Angle(values[i], values2[i]);
		}
		catch (const DivisionByZeroException& e)
		{
			Vec2F slerp;
			EXPECT_THROW(slerp = Vec2F::Slerp(values[i], values2[i], times[i]), DivisionByZeroException);
			continue;
		}
		catch (const NaNException& e)
		{
			Vec2F slerp;
			EXPECT_THROW(slerp = Vec2F::Slerp(values[i], values2[i], times[i]), NaNException);
			continue;
		}
		catch (...)
		{
			FAIL();
		}

		float sinAngle = Sin(angleBetween);
		float sinAngleT = Sin(times[i] * angleBetween);
		float sinAngle1T = Sin((1 - times[i]) * angleBetween);

		if (sinAngle == 0)
		{
			Vec2F slerp;
			EXPECT_THROW(slerp = Vec2F::Slerp(values[i], values2[i], times[i]), DivisionByZeroException);
			continue;
		}

		float tOnAngle = sinAngleT / sinAngle;
		float oneMinusTOnAngle = sinAngle1T / sinAngle;

		Vec2F slerp = vecAf * oneMinusTOnAngle + vecBf * tOnAngle;

		EXPECT_NEAR(slerp.X, Vec2F::Slerp(values[i], values2[i], times[i]).X, epsilon);
		EXPECT_NEAR(slerp.Y, Vec2F::Slerp(values[i], values2[i], times[i]).Y, epsilon);
	}
}

TEST_P(Vec2FTestFixtureMixedPair, Distance)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* values2 = pair.second;
	const auto epsilon = 0.0001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto distance = std::sqrt(std::pow(values[i].X - values2[i].X, 2) + std::pow(values[i].Y - values2[i].Y, 2));

		EXPECT_NEAR(distance, Vec2F::Distance(values[i], values2[i]), epsilon);
	}
}

TEST_P(Vec2FTestFixtureVecAndScalar, Rotate)
{
	auto pair = GetParam();
	auto* values = pair.first;
	auto* scalars = pair.second;
	const auto epsilon = 0.001f;

	for (size_t i = 0; i < ValuesSize; i++)
	{
		auto vecAf = values[i];
		auto result = values[i];
		auto angle = Radian(Degree(scalars[i]));

		const float cos = Cos(angle);
		const float sin = Sin(angle);

		auto x = vecAf.X * cos - vecAf.Y * sin;
		auto y = vecAf.X * sin + vecAf.Y * cos;

		vecAf.X = x;
		vecAf.Y = y;

		result.Rotate(angle);

		EXPECT_NEAR(vecAf.X, result.X, epsilon);
		EXPECT_NEAR(vecAf.Y, result.Y, epsilon);
	}
}

#pragma endregion