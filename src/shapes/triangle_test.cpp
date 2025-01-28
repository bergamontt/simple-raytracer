#include "gtest/gtest.h"
#include "triangle.h"

TEST(TriangleTest, TriangleIntersection1) {
	Triangle t(createPoint(0, 1, 0),
			   createPoint(-1, 0, 0),
			   createPoint(1, 0, 0));
	auto t1 = make_shared<Triangle>(t);
	Ray ray(createPoint(0, -1, -2),
			createVector(0, 1, 0));
	optional<Intersections> posXs = ray.intersect(t1);
	ASSERT_FALSE(posXs.has_value());
}

TEST(TriangleTest, TriangleIntersection2) {
	Triangle t(createPoint(0, 1, 0),
			   createPoint(-1, 0, 0),
			   createPoint(1, 0, 0));
	auto t1 = make_shared<Triangle>(t);
	Ray ray(createPoint(1, 1, -2),
			createVector(0, 0, 1));
	optional<Intersections> posXs = ray.intersect(t1);
	ASSERT_FALSE(posXs.has_value());
}

TEST(TriangleTest, TriangleIntersection3) {
	Triangle t(createPoint(0, 1, 0),
		createPoint(-1, 0, 0),
		createPoint(0, 0, 1));
	auto t1 = make_shared<Triangle>(t);
	Ray ray(createPoint(1, 1, -2),
		createVector(0, 0, 1));
	optional<Intersections> posXs = ray.intersect(t1);
	ASSERT_FALSE(posXs.has_value());
}

TEST(TriangleTest, TriangleIntersection4) {
	Triangle t(createPoint(0, 1, 0),
		createPoint(-1, 0, 0),
		createPoint(0, 0, 1));
	auto t1 = make_shared<Triangle>(t);
	Ray ray(createPoint(0, -1, -2),
		createVector(0, 0, 1));
	optional<Intersections> posXs = ray.intersect(t1);
	ASSERT_FALSE(posXs.has_value());
}

TEST(TriangleTest, TriangleIntersection5) {
	Triangle t(createPoint(0, 1, 0),
			   createPoint(-1, 0, 0),
			   createPoint(1, 0, 0));
	auto t1 = make_shared<Triangle>(t);
	Ray ray(createPoint(0, 0.5, -2),
			createVector(0, 0, 1));
	optional<Intersections> posXs = ray.intersect(t1);
	ASSERT_TRUE(posXs.has_value());
	Intersections xs = posXs.value();
	ASSERT_FLOAT_EQ(xs.get(0).time(), 2.0f);
}