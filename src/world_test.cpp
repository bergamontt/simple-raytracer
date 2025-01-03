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