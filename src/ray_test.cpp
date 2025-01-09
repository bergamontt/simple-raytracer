#include "gtest/gtest.h"
#include "ray.h"
#include "tuple.h"
#include "shapes/sphere.h"
#include "transformation.h"

TEST(RayTest, RayCreation)
{
	Tuple point = createPoint(1, 2, 3);
	Tuple direction = createVector(4, 5, 6);
	Ray r(point, direction);
	ASSERT_EQ(point, r.origin());
	ASSERT_EQ(direction, r.direction());
}

TEST(RayTest, ComputingDistance)
{
	Ray r(createPoint(2, 3, 4), createVector(1, 0, 0));
	ASSERT_EQ(r.position(0), createPoint(2, 3, 4));
	ASSERT_EQ(r.position(1), createPoint(3, 3, 4));
	ASSERT_EQ(r.position(-1), createPoint(1, 3, 4));
	ASSERT_EQ(r.position(2.5), createPoint(4.5, 3, 4));
}

TEST(RayTest, SphereIntersection1)
{
	Ray r(createPoint(0, 0, -5), createVector(0, 0, 1));
	auto s = make_shared<Sphere>();
	Intersections xs = r.intersect(s).value();
	ASSERT_EQ(xs.size(), 2);
	ASSERT_EQ(xs.get(1).time(), 6.0f);
	ASSERT_EQ(xs.get(0).time(), 4.0f);
}

TEST(RayTest, SphereIntersection2)
{
	Ray r(createPoint(0, 1, -5), createVector(0, 0, 1));
	auto s = make_shared<Sphere>();
	Intersections xs = r.intersect(s).value();
	ASSERT_EQ(xs.get(0).time(), 5.0f);
	ASSERT_EQ(xs.get(1).time(), 5.0f);
}

TEST(RayTest, SphereIntersection3)
{
	Ray r(createPoint(0, 2, -5), createVector(0, 0, 1));
	auto s = make_shared<Sphere>();
	ASSERT_FALSE(r.intersect(s).has_value());
}

TEST(RayTest, SphereIntersection4)
{
	Ray r(createPoint(0, 0, 0), createVector(0, 0, 1));
	auto s = make_shared<Sphere>();
	Intersections xs = r.intersect(s).value();
	ASSERT_EQ(xs.get(1).time(), 1.0f);
	ASSERT_EQ(xs.get(0).time(), -1.0f);
}

TEST(RayTest, SphereIntersection5)
{
	Ray r(createPoint(0, 0, 5), createVector(0, 0, 1));
	auto s = make_shared<Sphere>();
	Intersections xs = r.intersect(s).value();
	ASSERT_EQ(xs.get(1).time(), -4.0f);
	ASSERT_EQ(xs.get(0).time(), -6.0f);
}

TEST(RayTest, TranslatingRay1)
{
	Ray r(createPoint(1, 2, 3), createVector(0, 1, 0));
	Matrix m = translation(3, 4, 5);
	Ray tr = r.transform(m);
	ASSERT_EQ(tr.origin(), createPoint(4, 6, 8));
	ASSERT_EQ(tr.direction(), createVector(0, 1, 0));
}

TEST(RayTest, TranslatingRay2)
{
	Ray r(createPoint(1, 2, 3), createVector(0, 1, 0));
	Matrix m = scaling(2, 3, 4);
	Ray tr = r.transform(m);
	ASSERT_EQ(tr.origin(), createPoint(2, 6, 12));
	ASSERT_EQ(tr.direction(), createVector(0, 3, 0));
}