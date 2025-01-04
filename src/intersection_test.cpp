#include "gtest/gtest.h"
#include "intersections.h"
#include "computations.h"

TEST(IntersectionTest, IntersectionCreation)
{
	Sphere s;
	Intersection i(3.5, s);
	ASSERT_EQ(i.time(), 3.5);
	ASSERT_EQ(i.object(), s);
}

TEST(IntersectionTest, IntersectionHit1)
{
	Sphere s;
	Intersection i1(1, s);
	Intersection i2(2, s);

	Intersections xs;
	xs.add(i1);
	xs.add(i2);

	Intersection res = xs.hit().value();
	ASSERT_EQ(res, i1);
}

TEST(IntersectionTest, IntersectionHit2)
{
	Sphere s;
	Intersection i1(-1, s);
	Intersection i2(1, s);

	Intersections xs;
	xs.add(i1);
	xs.add(i2);

	Intersection res = xs.hit().value();
	ASSERT_EQ(res, i2);
}

TEST(IntersectionTest, IntersectionHit3)
{
	Sphere s;
	Intersection i1(-1, s);
	Intersection i2(-2, s);

	Intersections xs;
	xs.add(i1);
	xs.add(i2);

	ASSERT_FALSE(xs.hit().has_value());
}

TEST(IntersectionTest, IntersectionHit4)
{
	Sphere s;
	Intersection i1(5, s);
	Intersection i2(7, s);
	Intersection i3(-3, s);
	Intersection i4(2, s);

	Intersections xs;
	xs.add(i1);
	xs.add(i2);
	xs.add(i3);
	xs.add(i4);

	Intersection res = xs.hit().value();
	ASSERT_EQ(res, i4);
}

TEST(IntersectionTest, PrecomputingStateOfIntersection)
{
	Ray ray(createPoint(0, 0, -5), createVector(0, 0, 1));
	Sphere shape;
	optional<Intersections> xs = ray.intersect(shape);
	Intersections xss = xs.value();
	Intersection i = xss.get(0);
	Computations comps(i, ray);
	ASSERT_FLOAT_EQ(comps.time(), i.time());
	ASSERT_EQ(comps.point(), createPoint(0, 0, -1));
	ASSERT_EQ(comps.eyeVector(), createVector(0, 0, -1));
	ASSERT_EQ(comps.normalVector(), createVector(0, 0, -1));
}

TEST(IntersectionTest, IntersectionsOutside)
{
	Ray ray(createPoint(0, 0, -5), createVector(0, 0, 1));
	Sphere shape;
	optional<Intersections> xs = ray.intersect(shape);
	Intersections xss = xs.value();
	Intersection i = xss.get(0);
	Computations comps(i, ray);
	ASSERT_FALSE(comps.inside());
}

TEST(IntersectionTest, IntersectionsInside)
{
	Ray ray(createPoint(0, 0, 0), createVector(0, 0, 1));
	Sphere shape;
	optional<Intersections> xs = ray.intersect(shape);
	Intersections xss = xs.value();
	Intersection i = xss.get(1);
	Computations comps(i, ray);
	ASSERT_EQ(comps.point(), createPoint(0, 0, 1));
	ASSERT_EQ(comps.eyeVector(), createVector(0, 0, -1));
	ASSERT_TRUE(comps.inside());
	ASSERT_EQ(comps.normalVector(), createVector(0, 0, -1));
}