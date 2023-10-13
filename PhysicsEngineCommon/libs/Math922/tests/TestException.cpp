#include "gtest/gtest.h"
#include "Exception.h"

TEST(Exception, DivisionByZeroException)
{
	EXPECT_THROW(throw DivisionByZeroException(), DivisionByZeroException);
}

TEST(Exception, OutOfRangeException)
{
	EXPECT_THROW(throw OutOfRangeException(), OutOfRangeException);
}
