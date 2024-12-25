#include "gtest/gtest.h"
#include "color.h"
#include "func.h"

TEST(ColorTest, ColorCreation) {
	Color c = createColor(-0.5, 0.4, 1.7);
	ASSERT_FLOAT_EQ(c.red, -0.5);
	ASSERT_FLOAT_EQ(c.green, 0.4);
	ASSERT_FLOAT_EQ(c.blue, 1.7);
}

TEST(ColorTest, ColorAddition) {
	Color c1 = createColor(0.9, 0.6, 0.75);
	Color c2 = createColor(0.7, 0.1, 0.25);
	Color res = createColor(1.6, 0.7, 1.0);
	ASSERT_EQ(c1 + c2, res);
}

TEST(ColorTest, ColorSubtraction) {
	Color c1 = createColor(0.9, 0.6, 0.75);
	Color c2 = createColor(0.7, 0.1, 0.25);
	Color res = createColor(0.2, 0.5, 0.5);
	ASSERT_EQ(c1 - c2, res);
}

TEST(ColorTest, ColorScalarMultiplication) {
	Color c1 = createColor(0.2, 0.3, 0.4);
	Color res = createColor(0.4, 0.6, 0.8);
	ASSERT_EQ(c1 * 2, res);
}

TEST(ColorTest, ColorMultiplication) {
	Color c1 = createColor(1, 0.2, 0.4);
	Color c2 = createColor(0.9, 1, 0.1);
	Color res = createColor(0.9, 0.2, 0.04);
	ASSERT_EQ(c1 * c2, res);
}