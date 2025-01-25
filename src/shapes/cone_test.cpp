#include "gtest/gtest.h"
#include "cone.h"

TEST(ConeTest, LocalIntersectionHits)
{
	auto c = make_shared<Cone>();
	Ray ray(createPoint(1, 1, -5), normalize(createVector(-0.5, -1, 1)));
	optional<Intersections> posXs = c->localIntersection(ray);
	Intersections xs = posXs.value();
	ASSERT_EQ(xs.size(), 2);
	ASSERT_TRUE(equalDouble(xs.get(0).time(), 4.55006f));
	ASSERT_TRUE(equalDouble(xs.get(1).time(), 49.44994f));
}

TEST(ConeTest, LocalIntersectionHitsParallel)
{
	auto c = make_shared<Cone>();
	Ray ray(createPoint(0, 0, -1), normalize(createVector(0, 1, 1)));
	optional<Intersections> posXs = c->localIntersection(ray);
	Intersections xs = posXs.value();
	ASSERT_EQ(xs.size(), 1);
	ASSERT_TRUE(equalDouble(xs.get(0).time(), 0.35355f));
}

TEST(ConeTest, LocalIntersectionClosed)
{
	auto c = make_shared<Cone>();
	c->setMinimum(-0.5);
	c->setMaximum(0.5);
	c->setCapped(true);
	Ray ray(createPoint(0, 0, -0.25), normalize(createVector(0, 1, 0)));
	optional<Intersections> posXs = c->localIntersection(ray);
	ASSERT_TRUE(posXs.has_value());
	ASSERT_EQ(posXs.value().size(), 4);
}

TEST(ConeTest, NormalAtClosed)
{
	auto c = make_shared<Cone>();
	Tuple normal = c->normalAt(createPoint(-1, -1, 0));
	ASSERT_EQ(normal, normalize(createVector(-1, 1, 0)));
}