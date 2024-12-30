#include "gtest/gtest.h"
#include "intersection.h"

TEST(IntersectionTest, IntersectionCreation)
{
	Sphere s;
	Intersection i(3.5, s);
	ASSERT_EQ(i.time(), 3.5);
	ASSERT_EQ(i.object(), s);
}