#include "gtest/gtest.h"
#include "cube.h"
#include "../ray.h"

TEST(CubeTest, RayCubeIntersection)
{
	auto c = make_shared<Cube>();
	Ray r(createPoint(5, 0.5, 0), createVector(-1, 0, 0));
	optional<Intersections> posXs = c->localIntersection(r);
	Intersections xs = posXs.value();
	ASSERT_TRUE(xs.size() == 2);
	ASSERT_FLOAT_EQ(xs.get(0).time(), 4.0f);
	ASSERT_FLOAT_EQ(xs.get(1).time(), 6.0f);
}

TEST(CubeTest, RayMissesTheCube)
{
	auto c = make_shared<Cube>();
	Ray r(createPoint(-2, 0, 0), createVector(0.2673, 0.5345, 0.8018));
	optional<Intersections> posXs = c->localIntersection(r);
	ASSERT_FALSE(posXs.has_value());
}

TEST(CubeTest, NormalAtCube)
{
	auto c = make_shared<Cube>();
	Tuple point = createPoint(1, 0.5, -0.8);
	Tuple normal = c->normalAt(point);
	ASSERT_EQ(normal, createVector(1, 0, 0));
}