#include "gtest/gtest.h"
#include "../transformation.h"
#include "../intersections.h"
#include "../ray.h"
#include "sphere.h"
#include <numbers>

using namespace std::numbers;

TEST(SphereTest, SphereTransforamtion1)
{
	Sphere s;
	Matrix m = s.transform();
	ASSERT_EQ(s.transform(), Matrix::indentityMatrix(TRANSFORM_N));
}

TEST(SphereTest, SphereTransforamtion2)
{
	Sphere s;
	Matrix t = translation(2, 3, 4);
	s.setTransform(t);
	ASSERT_EQ(s.transform(), t);
}

TEST(SphereTest, SphereIntersection)
{
	auto s = make_shared<Sphere>();
	Ray r = { createPoint(0, 0, -5), createVector(0, 0, 1) };
	s->setTransform(scaling(2, 2, 2));
	Intersections xs = r.intersect(s).value();
	ASSERT_EQ(xs.size(), 2);
	ASSERT_EQ(xs.get(0).time(), 3);
	ASSERT_EQ(xs.get(1).time(), 7);
}

TEST(SphereTest, SphereNormalVector1)
{
	Sphere s;
	Tuple n = s.normalAt(createPoint(1, 0, 0));
	ASSERT_EQ(n, createVector(1, 0, 0));
}

TEST(SphereTest, SphereNormalVector2)
{
	Sphere s;
	Tuple n = s.normalAt(createPoint(0, 1, 0));
	ASSERT_EQ(n, createVector(0, 1, 0));
}

TEST(SphereTest, SphereNormalVector3)
{
	Sphere s;
	Tuple n = s.normalAt(createPoint(0, 0, 1));
	ASSERT_EQ(n, createVector(0, 0, 1));
}

TEST(SphereTest, NormalVectorsAreNormalized)
{
	Sphere s;
	Tuple n = s.normalAt(createPoint(2, 2, 2));
	ASSERT_EQ(n, normalize(n));
}

TEST(SphereTest, NormalOnTranslatedSphere)
{
	Sphere s;
	s.setTransform(translation(0, 1, 0));
	Tuple n = s.normalAt(createPoint(0, 1.70711, -0.70711));
	ASSERT_EQ(n, createVector(0, 0.70711, -0.70711));
}

TEST(SphereTest, NormalOnTransformedSphere)
{
	Sphere s;
	Matrix m = scaling(1, 0.5, 1) * rotationZ(pi / 5);
	s.setTransform(m);
	Tuple n = s.normalAt(createPoint(0, sqrt(2) / 2, -sqrt(2) / 2));
	ASSERT_EQ(n, createVector(0, 0.97014, -0.24254));
}

TEST(SphereTest, SphereMaterialTest)
{
	Sphere s;
	Material m = s.material();
	m.ambient = 1.0f;
	s.setMaterial(m);
	ASSERT_EQ(m, s.material());
}