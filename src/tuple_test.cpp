#include "gtest/gtest.h"
#include "tuple.h"
#include "func.h"

TEST(PointTest, CreatingPoint) {
	Tuple a = createPoint(4.3, -4.2, 3.1);
	ASSERT_FLOAT_EQ(a.x, 4.3);
	ASSERT_FLOAT_EQ(a.y, -4.2);
	ASSERT_FLOAT_EQ(a.z, 3.1);
	ASSERT_FLOAT_EQ(a.w, 1.0);
	ASSERT_TRUE(isPoint(a));
	ASSERT_FALSE(isVector(a));
}

TEST(VectorTest, CreatingVector) {
	Tuple a = createVector(4.3, -4.2, 3.1);
	ASSERT_FLOAT_EQ(a.x, 4.3);
	ASSERT_FLOAT_EQ(a.y, -4.2);
	ASSERT_FLOAT_EQ(a.z, 3.1);
	ASSERT_FLOAT_EQ(a.w, 0.0);
	ASSERT_FALSE(isPoint(a));
	ASSERT_TRUE(isVector(a));
}

TEST(TupleTest, AddingTuples) {
	Tuple a = createPoint(3, -2, 5);
	Tuple b = createVector(-2, 3, 1);
	Tuple result = createPoint(1, 1, 6);
	ASSERT_TRUE(a + b == result);
}

TEST(TupleTest, SubtractingTwoPoints) {
	Tuple a = createPoint(3, 2, 1);
	Tuple b = createPoint(5, 6, 7);
	Tuple result = createVector(-2, -4, -6);
	ASSERT_TRUE(a - b == result);
}

TEST(TupleTest, SubtractingVectorFromPoint) {
	Tuple a = createPoint(3, 2, 1);
	Tuple b = createVector(5, 6, 7);
	Tuple result = createPoint(-2, -4, -6);
	ASSERT_TRUE(a - b == result);
}

TEST(TupleTest, SubtractingTwoVectors) {
	Tuple a = createVector(3, 2, 1);
	Tuple b = createVector(5, 6, 7);
	Tuple result = createVector(-2, -4, -6);
	ASSERT_TRUE(a - b == result);
}

TEST(TupleTest, SubtractingVectorFromZeroVector) {
	Tuple zeroVector = createVector(0.0, 0.0, 0.0);
	Tuple v = createVector(1, -2, 3);
	Tuple res = createVector(-1, 2, -3);
	ASSERT_TRUE(zeroVector - v == res);
}

TEST(TupleTest, NegatingTuple) {
	Tuple a = createTuple(1, -2, 3, -4);
	Tuple res = createTuple(-1, 2, -3, 4);
	ASSERT_TRUE(-a == res);
}

TEST(TupleTest, NormalizeVector1) {
	Tuple a = createVector(4, 0, 0);
	Tuple res = createVector(1, 0, 0);
	ASSERT_TRUE(normalize(a) == res);
}

TEST(TupleTest, NormalizeVector2) {
	Tuple a = createVector(1, 2, 3);
	Tuple res = createVector(0.26726, 0.53452, 0.80178);
	ASSERT_TRUE(normalize(a) == res);
}

TEST(TupleTest, MagnitudeOfNormalizedVector) {
	Tuple a = createVector(1, 2, 3);
	Tuple norm = normalize(a);
	ASSERT_FLOAT_EQ(magnitude(norm), 1.0);
}

TEST(TupleTest, DotProductOfTwoTuples) {
	Tuple a = createVector(1, 2, 3);
	Tuple b = createVector(2, 3, 4);
	ASSERT_FLOAT_EQ(dot(a, b), 20);
}

TEST(TupleTest, CrossProductOfTwoVectors) {
	Tuple a = createVector(1, 2, 3);
	Tuple b = createVector(2, 3, 4);
	Tuple res = createVector(-1, 2, -1);
	ASSERT_TRUE(cross(a, b) == res);
}