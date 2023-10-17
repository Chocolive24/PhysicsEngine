//
// Created by remla on 02/10/2023.
//
#include "gtest/gtest.h"
#include "Angle.h"
#include "lookupTables/LookUpTableCot.h"
#include "MathUtility.h"

struct AngleFixture : public ::testing::TestWithParam<std::vector<Radian>>
{
};

TEST_P(AngleFixture, CotWithLUT)
{
    auto angles = GetParam();

    for (auto a : angles)
    {
        EXPECT_NEAR(MathUtility::CotLut(a), 1/std::tan(static_cast<float>(a)), 0.001f);
    }
}

TEST_P(AngleFixture, CotWithTaylorSeries)
{
    auto angles = GetParam();

    for (auto a : angles)
    {
        EXPECT_NEAR(MathUtility::Cot(a),  1/std::tan(static_cast<float>(a)), 0.001f);
    }
}

std::vector<Radian> GetRadianAngles()
{
    std::vector<Radian> v;

    // Value to be withdrawn from the start and the end of the range, because tan isn't precise for values
    // too far from zero.
    int errorMargin = 12;

    v.reserve(CotTableSize - 2 * errorMargin);
    float value = MathUtility::CotRangeStart + static_cast<float>(errorMargin) * MathUtility::CotStepSize;

    for (int i = 0; i < CotTableSize - 2 * errorMargin; i++)
    {
        Radian r(value);
        v.push_back(r);
        value += MathUtility::CotStepSize;
    }

    return v;
}

INSTANTIATE_TEST_SUITE_P(Angles, AngleFixture, testing::Values(
        GetRadianAngles()
));