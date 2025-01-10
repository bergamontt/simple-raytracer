#include "gtest/gtest.h"
#include "../transformation.h"
#include "../intersections.h"
#include "../ray.h"
#include "plane.h"

TEST(PlaneTest, ConstantNormalOfAPlane)
{
	Plane p;
	Tuple n1 = p.normalAt(createPoint(0, 0, 0));
	Tuple n2 = p.normalAt(createPoint(10, 0, -10));
	Tuple n3 = p.normalAt(createPoint(-5, 0, 150));

	ASSERT_EQ(n1, createVector(0, 1, 0));
	ASSERT_EQ(n2, createVector(0, 1, 0));
	ASSERT_EQ(n3, createVector(0, 1, 0));
}

TEST(PlaneTest, IntersectPlaneWithParallelRay)
{
	Plane p;
	Ray ray(createPoint(0, 10, 0), createVector(0, 0, 1));
	optional<Intersections> xs = p.localIntersection(ray);
	ASSERT_FALSE(xs.has_value());
}

TEST(PlaneTest, IntersectPlaneWithComplanarRay)
{
	Plane p;
	Ray ray(createPoint(0, 0, 0), createVector(0, 0, 1));
	optional<Intersections> xs = p.localIntersection(ray);
	ASSERT_FALSE(xs.has_value());
}

TEST(PlaneTest, RayIntersectingFromAbove)
{
	auto p = make_shared<Plane>();
	Ray ray(createPoint(0, 1, 0), createVector(0, -1, 0));
	optional<Intersections> possibleXs = ray.intersect(p);
	Intersections xs = possibleXs.value();
	ASSERT_EQ(xs.size(), 1);
	Intersection fst = xs.get(0);
	ASSERT_FLOAT_EQ(fst.time(), 1);
}

TEST(PlaneTest, RayIntersectingFromBelow)
{
	auto p = make_shared<Plane>();
	Ray ray(createPoint(0, -1, 0), createVector(0, 1, 0));
	optional<Intersections> possibleXs = ray.intersect(p);
	Intersections xs = possibleXs.value();
	ASSERT_EQ(xs.size(), 1);
	Intersection fst = xs.get(0);
	ASSERT_FLOAT_EQ(fst.time(), 1);
}