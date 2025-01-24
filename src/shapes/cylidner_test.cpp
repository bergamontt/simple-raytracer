#include "gtest/gtest.h"
#include "cylinder.h"

TEST(CylinderTest, LocalIntersectionMisses)
{
	auto c = make_shared<Cylinder>();
	Ray ray(createPoint(1, 0, 0), (createVector(0, 1, 0)));
	optional<Intersections> posXs = c->localIntersection(ray);
	ASSERT_FALSE(posXs.has_value());
}

TEST(CylinderTest, LocalIntersectionHits)
{
	auto c = make_shared<Cylinder>();
	Ray ray(createPoint(1, 0, -5), normalize(createVector(0, 0, 1)));
	optional<Intersections> posXs = c->localIntersection(ray);
	Intersections xs = posXs.value();
	ASSERT_EQ(xs.size(), 2);
	ASSERT_FLOAT_EQ(xs.get(0).time(), 5.0f);
	ASSERT_FLOAT_EQ(xs.get(1).time(), 5.0f);
}

TEST(CylinderTest, NormalVector)
{
	auto c = make_shared<Cylinder>();
	Tuple res = c->normalAt(createPoint(1, 0, 0));
	ASSERT_EQ(res, createVector(1, 0, 0));
}

TEST(CylinderTest, LocalIntersectionConstrained)
{
	auto c = make_shared<Cylinder>();
	c->setMinimum(1.0f);
	c->setMaximum(2.0f);
	Ray ray(createPoint(0, 1.5, 0), normalize(createVector(0.1, 1, 0)));
	optional<Intersections> posXs = c->localIntersection(ray);
	ASSERT_FALSE(posXs.has_value());
}

TEST(CylinderTest, LocalIntersectionClosed)
{
	auto c = make_shared<Cylinder>();
	c->setMinimum(1.0f);
	c->setMaximum(2.0f);
	c->setCapped(true);
	Ray ray(createPoint(0, 3, 0), normalize(createVector(0, -1, 0)));
	optional<Intersections> posXs = c->localIntersection(ray);
	ASSERT_TRUE(posXs.has_value());
}

TEST(CylinderTest, NormalAtClosed)
{
	auto c = make_shared<Cylinder>();
	c->setMinimum(1.0f);
	c->setMaximum(2.0f);
	c->setCapped(true);
	Tuple normal = c->normalAt(createPoint(0.5, 1, 0));
	ASSERT_EQ(normal, createVector(0, -1, 0));
}