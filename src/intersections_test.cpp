#include "gtest/gtest.h"
#include "intersections.h"
#include "shapes/plane.h"
#include "computations.h"
#include "transformation.h"

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

TEST(IntersectionsTest, ComputingRefractingIndeces)
{
	Sphere s1 = Sphere::glassSphere();
	s1.setTransform(scaling(2, 2, 2));
	s1.material().reflactiveIndex = 1.5f;
	auto ss1 = make_shared<Sphere>(s1);

	Sphere s2 = Sphere::glassSphere();
	s2.setTransform(translation(0, 0, -0.25));
	s2.material().reflactiveIndex = 2.0f;
	auto ss2 = make_shared<Sphere>(s2);

	Sphere s3 = Sphere::glassSphere();
	s2.setTransform(translation(0, 0, 0.25));
	s3.material().reflactiveIndex = 2.5f;
	auto ss3 = make_shared<Sphere>(s3);

	Ray ray(createPoint(0, 0, -4), createVector(0, 0, 1));
	
	Intersections xs;

	optional<Intersections> s1xs = ray.intersect(ss1);
	optional<Intersections> s2xs = ray.intersect(ss2);
	optional<Intersections> s3xs = ray.intersect(ss3);

	xs.merge(s1xs.value());
	xs.merge(s2xs.value());
	xs.merge(s3xs.value());

	Computations comps(xs.get(0), ray, xs);
	ASSERT_FLOAT_EQ(comps.n1(), 1.0f);
	ASSERT_FLOAT_EQ(comps.n2(), 1.5f);
}

TEST(IntersectionsTest, UnderPointOffset)
{
	Ray ray(createPoint(0, 0, -5), createVector(0, 0, 1));
	Sphere s1 = Sphere::glassSphere();
	s1.setTransform(translation(0, 0, 1));

	auto glassSph = make_shared<Sphere>(s1);
	Intersection i(5, glassSph);

	optional<Intersections> posXs = ray.intersect(glassSph);
	Intersections xs = posXs.value();

	Computations comp(i, ray, xs);
	ASSERT_TRUE(comp.underPoint()._z > EPSILON / 2);
	ASSERT_TRUE(comp.underPoint()._z > comp.point()._z);
}

TEST(IntersectionsTest, SchlickTotalReflection)
{
	
	Sphere s1 = Sphere::glassSphere();
	auto ss1 = make_shared<Sphere>(s1);

	Ray ray(createPoint(0, 0, - sqrt(2) / 2), createVector(0, 1, 0));
	optional<Intersections> posXs = ray.intersect(ss1);
	Intersections xs = posXs.value();
	Computations comp(xs.get(1), ray, xs);
	float reflectance = comp.schlick();
	ASSERT_FLOAT_EQ(reflectance, 1.0f);
}

TEST(IntersectionsTest, SchlickPerpendicularAngle)
{

	Sphere s1 = Sphere::glassSphere();
	auto ss1 = make_shared<Sphere>(s1);

	Ray ray(createPoint(0, 0, 0), createVector(0, 1, 0));
	optional<Intersections> posXs = ray.intersect(ss1);
	Intersections xs = posXs.value();

	Computations comp(xs.get(1), ray, xs);
	
	float reflectance = comp.schlick();
	ASSERT_TRUE(reflectance >= 0.04);
}


TEST(IntersectionsTest, SchlickSmallAngle)
{

	Sphere s1 = Sphere::glassSphere();
	auto ss1 = make_shared<Sphere>(s1);

	Ray ray(createPoint(0, 0.99, -2), createVector(0, 0, 1));
	optional<Intersections> posXs = ray.intersect(ss1);
	Intersections xs = posXs.value();

	Computations comp(xs.get(0), ray, xs);

	float reflectance = comp.schlick();
	ASSERT_TRUE(reflectance >= 0.48873f);
}