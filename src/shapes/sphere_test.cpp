#include "gtest/gtest.h"
#include "../transformation.h"
#include "../intersections.h"
#include "../ray.h"
#include "sphere.h"

TEST(SphereTest, SphereTransforamtion1)
{
	Sphere s;
	Matrix m = s.transform();
	ASSERT_EQ(s.transform(), Matrix::indentityMatrix(TRANSFORM_N));
}

TEST(SphereTest, SphereTransforamtion2)
{
	Sphere s;
	Matrix t = translation(2, 3, 4);
	s.setTransform(t);
	ASSERT_EQ(s.transform(), t);
}

TEST(SphereTest, SphereIntersection)
{
	Sphere s;
	Ray r = { createPoint(0, 0, -5), createVector(0, 0, 1) };
	s.setTransform(scaling(2, 2, 2));
	Intersections xs = r.intersect(s).value();
	ASSERT_EQ(xs.size(), 2);
	ASSERT_EQ(xs.get(0).time(), 3);
	ASSERT_EQ(xs.get(1).time(), 7);
}