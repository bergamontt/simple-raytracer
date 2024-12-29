#include "gtest/gtest.h"
#include "ray.h"

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
	Sphere s;
	vector<float> xs = r.intersect(s);
	ASSERT_EQ(xs.size(), 2);
	ASSERT_EQ(xs.back(), 6.0f);
	xs.pop_back();
	ASSERT_EQ(xs.back(), 4.0f);
}

TEST(RayTest, SphereIntersection2)
{
	Ray r(createPoint(0, 1, -5), createVector(0, 0, 1));
	Sphere s;
	vector<float> xs = r.intersect(s);
	ASSERT_EQ(xs.back(), 5.0f);
	xs.pop_back();
	ASSERT_EQ(xs.back(), 5.0f);
}

TEST(RayTest, SphereIntersection3)
{
	Ray r(createPoint(0, 2, -5), createVector(0, 0, 1));
	Sphere s;
	vector<float> xs = r.intersect(s);
	ASSERT_EQ(xs.size(), 0);
}

TEST(RayTest, SphereIntersection4)
{
	Ray r(createPoint(0, 0, 0), createVector(0, 0, 1));
	Sphere s;
	vector<float> xs = r.intersect(s);
	ASSERT_EQ(xs.back(), 1.0f);
	xs.pop_back();
	ASSERT_EQ(xs.back(), -1.0f);
}

TEST(RayTest, SphereIntersection5)
{
	Ray r(createPoint(0, 0, 5), createVector(0, 0, 1));
	Sphere s;
	vector<float> xs = r.intersect(s);
	ASSERT_EQ(xs.back(), -4.0f);
	xs.pop_back();
	ASSERT_EQ(xs.back(), -6.0f);
}