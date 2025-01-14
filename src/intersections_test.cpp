#include "gtest/gtest.h"
#include "intersections.h"
#include "shapes/plane.h"
#include "computations.h"

TEST(IntersectionsTest, ComputingReflectVector)
{
	Plane s;
	auto shape = make_shared<Plane>(s);
	Ray ray(createPoint(0, 1, -1), createVector(0, - 2 * sqrt(2), 2 * sqrt(2)));
	optional<Intersections> posInters = ray.intersect(shape);
	Intersections inters = posInters.value();
	Computations comp(inters.get(0), ray);
	ASSERT_EQ(comp.reflectVector(), createVector(0, 2 * sqrt(2), 2 * sqrt(2)));
}