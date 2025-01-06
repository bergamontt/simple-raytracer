#include "gtest/gtest.h"
#include "transformation.h"
#include "world.h"

using namespace std;

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

TEST(WorldTest, ColorWhenARayMisses)
{
	World w = World::defaultWorld();
	Ray r(createPoint(0, 0, -5), createVector(0, 1, 0));
	Color res = w.colorAt(r);
	ASSERT_EQ(res, createColor(0, 0, 0));
}

TEST(WorldTest, ColorWhenARayHits)
{
	World w = World::defaultWorld();
	Ray r(createPoint(0, 0, -5), createVector(0, 0, 1));
	Color res = w.colorAt(r);
	ASSERT_EQ(res, createColor(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColorWhithIntersectionBehindTheRay)
{
	World w = World::defaultWorld();

	Sphere& outer = w.getChangeableObject(0);
	Material outerm = outer.material();
	outerm.ambient = 1.0f;
	outer.setMaterial(outerm);

	Sphere& inner = w.getChangeableObject(1);
	Material innerm = inner.material();
	innerm.ambient = 1.0f;
	inner.setMaterial(innerm);

	Ray r(createPoint(0, 0, 0.75), createVector(0, 0, -1));

	Color res = w.colorAt(r);
	ASSERT_EQ(res, innerm.color);
}

TEST(WorldTest, ShadowedArea1)
{
	World w = World::defaultWorld();
	Tuple point = createPoint(0, 10, 0);
	ASSERT_FALSE(w.isShadowed(point));
}

TEST(WorldTest, ShadowedArea2)
{
	World w = World::defaultWorld();
	Tuple point = createPoint(10, -10, 10);
	ASSERT_TRUE(w.isShadowed(point));
}

TEST(WorldTest, ShadowedArea3)
{
	World w = World::defaultWorld();
	Tuple point = createPoint(-20, 20, -20);
	ASSERT_FALSE(w.isShadowed(point));
}

TEST(WorldTest, ShadowedArea4)
{
	World w = World::defaultWorld();
	Tuple point = createPoint(-2, 2, -2);
	ASSERT_FALSE(w.isShadowed(point));
}

TEST(WorldTest, ShadeHitInShadow)
{
	World w;
	w.setLight({ createPoint(0, 0, -10), createColor(1, 1, 1) });
	
	Sphere s1;
	w.addObject(s1);

	Sphere s2;
	s2.setTransform(translation(0, 0, 10));
	w.addObject(s2);

	Ray ray(createPoint(0, 0, 5), createVector(0, 0, 1));
	optional<Intersections> xs = ray.intersect(s2);
	Intersections intersections = xs.value();
	Intersection i = intersections.get(0);

	Computations comp(i, ray);
	Color color = w.shadeHit(comp);
	ASSERT_EQ(color, createColor(0.1, 0.1, 0.1));
}