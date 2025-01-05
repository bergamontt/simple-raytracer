#include "gtest/gtest.h"
#include "matrix.h"
#include "transformation.h"
#include "tuple.h"
#include <numbers>

using std::numbers::pi;

TEST(TransformationTest, TranslationMatrix)
{
	Matrix transform = translation(5, -3, 2);
	Tuple point = createPoint(-3, 4, 5);
	Tuple result = transform * point;
	Tuple suppRes = createPoint(2, 1, 7);
	ASSERT_EQ(result, suppRes);
}

TEST(TransformationTest, InverseTranslationMatrix)
{
	Matrix transform = translation(5, -3, 2);
	Matrix inv = transform.inverse();
	Tuple point = createPoint(-3, 4, 5);
	Tuple suppRes = createPoint(-8, 7, 3);
	ASSERT_EQ(inv * point, suppRes);
}

TEST(TransformationTest, TranslationOfVector)
{
	Matrix transform = translation(5, -3, 2);
	Tuple vector = createVector(-3, 4, 5);
	ASSERT_EQ(transform * vector, vector);
}

TEST(TransformationTest, ScalingPoint)
{
	Matrix transform = scaling(2, 3, 4);
	Tuple point = createPoint(-4, 6, 8);
	ASSERT_EQ(transform * point, createPoint(-8, 18, 32));
}

TEST(TransformationTest, ScalingVector)
{
	Matrix transform = scaling(2, 3, 4);
	Tuple vector = createVector(-4, 6, 8);
	ASSERT_EQ(transform * vector, createVector(-8, 18, 32));
}

TEST(TransformationTest, InverseScalingVector)
{
	Matrix transform = scaling(2, 3, 4);
	Matrix inv = transform.inverse();
	Tuple vector = createVector(-4, 6, 8);
	ASSERT_EQ(inv * vector, createVector(-2, 2, 2));
}

TEST(TransformationTest, ReflectionScaling) {
	Matrix transform = scaling(-1, 1, 1);
	Tuple point = createPoint(2, 3, 4);
	ASSERT_EQ(transform * point, createPoint(-2, 3, 4));
}

TEST(TransformationTest, RotationX)
{
	Tuple point = createPoint(0, 1, 0);
	Matrix half_quarter = rotationX(pi / 4);
	Matrix full_quarter = rotationX(pi / 2);
	ASSERT_EQ(half_quarter * point, createPoint(0, sqrt(2) / 2, sqrt(2) / 2));
	ASSERT_EQ(full_quarter * point, createPoint(0, 0, 1));
}

TEST(TransformationTest, RotationY)
{
	Tuple point = createPoint(0, 0, 1);
	Matrix half_quarter = rotationY(pi / 4);
	Matrix full_quarter = rotationY(pi / 2);
	ASSERT_EQ(half_quarter * point, createPoint(sqrt(2) / 2, 0, sqrt(2) / 2));
	ASSERT_EQ(full_quarter * point, createPoint(1, 0, 0));
}

TEST(TransformationTest, RotationZ)
{
	Tuple point = createPoint(0, 1, 0);
	Matrix half_quarter = rotationZ(pi / 4);
	Matrix full_quarter = rotationZ(pi / 2);
	ASSERT_EQ(half_quarter * point, createPoint(-sqrt(2) / 2, sqrt(2) / 2, 0));
	ASSERT_EQ(full_quarter * point, createPoint(-1, 0, 0));
}

TEST(TransformationTest, Skew1)
{
	Matrix transform = skew(1, 0, 0, 0, 0, 0);
	Tuple point = createPoint(2, 3, 4);
	ASSERT_EQ(transform * point, createPoint(5, 3, 4));
}

TEST(TransformationTest, Skew2)
{
	Matrix transform = skew(0, 1, 0, 0, 0, 0);
	Tuple point = createPoint(2, 3, 4);
	ASSERT_EQ(transform * point, createPoint(6, 3, 4));
}

TEST(TransformationTest, Skew3)
{
	Matrix transform = skew(0, 0, 1, 0, 0, 0);
	Tuple point = createPoint(2, 3, 4);
	ASSERT_EQ(transform * point, createPoint(2, 5, 4));
}

TEST(TransformationTest, Skew4)
{
	Matrix transform = skew(0, 0, 0, 1, 0, 0);
	Tuple point = createPoint(2, 3, 4);
	ASSERT_EQ(transform * point, createPoint(2, 7, 4));
}

TEST(TransformationTest, Skew5)
{
	Matrix transform = skew(0, 0, 0, 0, 1, 0);
	Tuple point = createPoint(2, 3, 4);
	ASSERT_EQ(transform * point, createPoint(2, 3, 6));
}

TEST(TransformationTest, Skew6)
{
	Matrix transform = skew(0, 0, 0, 0, 0, 1);
	Tuple point = createPoint(2, 3, 4);
	ASSERT_EQ(transform * point, createPoint(2, 3, 7));
}

TEST(TransformationTest, SequenceTransformations)
{
	Tuple point = createPoint(1, 0, 1);
	Matrix a = rotationX(pi / 2);
	Matrix b = scaling(5, 5, 5);
	Matrix c = translation(10, 5, 7);
	Tuple point2 = a * point;
	ASSERT_EQ(point2, createPoint(1, -1, 0));
	Tuple point3 = b * point2;
	ASSERT_EQ(point3, createPoint(5, -5, 0));
	Tuple point4 = c * point3;
	ASSERT_EQ(point4, createPoint(15, 0, 7));
	ASSERT_EQ((c * b * a) * point, createPoint(15, 0, 7));
}

TEST(TransformationTest, DefaultOrientation)
{
	Tuple from = createPoint(0, 0, 0);
	Tuple to = createPoint(0, 0, -1);
	Tuple up = createVector(0, 1, 0);
	Matrix t = viewTransform(from, to, up);
	ASSERT_EQ(t, Matrix::indentityMatrix(TRANSFORM_N));
}

TEST(TransformationTest, ViewTramsformationPositiveZ)
{
	Tuple from = createPoint(0, 0, 0);
	Tuple to = createPoint(0, 0, 1);
	Tuple up = createVector(0, 1, 0);
	Matrix t = viewTransform(from, to, up);
	ASSERT_EQ(t, scaling(-1, 1, -1));
}

TEST(TransformationTest, ViewTransformationMovesTheWorld)
{
	Tuple from = createPoint(0, 0, 8);
	Tuple to = createPoint(0, 0, 1);
	Tuple up = createVector(0, 1, 0);
	Matrix t = viewTransform(from, to, up);
	ASSERT_EQ(t, translation(0, 0, -8));
}

TEST(TransformationTest, ArbitraryViewTransformation)
{
	Tuple from = createPoint(1, 3, 2);
	Tuple to = createPoint(4, -2, 8);
	Tuple up = createVector(1, 1, 0);
	Matrix t = viewTransform(from, to, up);
	float arr[] = { -0.50709, 0.50709,  0.67612, -2.36643,
					 0.76772, 0.60609,  0.12122, -2.82843,
					-0.35857, 0.59761, -0.71714,  0.00000,
					 0.00000, 0.00000,  0.00000,  1.00000 };
	Matrix result(arr, TRANSFORM_N);
	ASSERT_EQ(t, result);
}