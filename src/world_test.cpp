#include "gtest/gtest.h"
#include "transformation.h"
#include "world.h"

TEST(WorldTest, IntersectWorld)
{
	World w = World::defaultWorld();
	Ray r(createPoint(0, 0, -5), createVector(0, 0, 1));
	optional<Intersections> xs = w.intersect(r);
	ASSERT_TRUE(xs.has_value());
	Intersections intrs = xs.value();
	ASSERT_FLOAT_EQ(intrs.get(0).time(), 4.0f);
	ASSERT_FLOAT_EQ(intrs.get(1).time(), 4.5f);
	ASSERT_FLOAT_EQ(intrs.get(2).time(), 5.5f);
	ASSERT_FLOAT_EQ(intrs.get(3).time(), 6.0f);
}

TEST(WorldTest, ShadingIntersectionOutside)
{
	World w = World::defaultWorld();
	Ray r(createPoint(0, 0, -5), createVector(0, 0, 1));
	Sphere s = w.getObject(0);
	optional<Intersections> xs = r.intersect(s);
	Intersections intrs = xs.value();
	Intersection i = intrs.get(0);
	Computations comp(i, r);
	Color c = w.shadeHit(comp);
	ASSERT_EQ(c, createColor(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ShadingIntersectionInside)
{
	World w = World::defaultWorld();
	w.setLight({createPoint(0, 0.25, 0), createColor(1, 1, 1)});
	Ray r(createPoint(0, 0, 0), createVector(0, 0, 1));
	Sphere s = w.getObject(1);
	optional<Intersections> xs = r.intersect(s);
	Intersections intrs = xs.value();
	Intersection i = intrs.get(1);
	Computations comp(i, r);
	Color c = w.shadeHit(comp);
	ASSERT_EQ(c, createColor(0.90498, 0.90498, 0.90498));
}