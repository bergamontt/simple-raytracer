#include "gtest/gtest.h"
#include "light.h"
#include "material.h"

using namespace std;

TEST(LightTest, LightCreation)
{
	Color intensity = createColor(1, 1, 1);
	Tuple position = createPoint(0, 0, 0);
	Light lightPoint(position, intensity);
	ASSERT_EQ(lightPoint.intensity(), intensity);
	ASSERT_EQ(lightPoint.position(), position);
}

TEST(LightTest, MaterialLightning1)
{
	Material m;
	Tuple position = createPoint(0, 0, 0);
	Tuple eyev = createVector(0, 0, -1);
	Tuple normalv = createVector(0, 0, -1);
	Light light(createPoint(0 ,0, -10), WHITE);
	Color result = lightning(m, light, position, eyev, normalv);
	ASSERT_EQ(result, createColor(1.9, 1.9, 1.9));
}

TEST(LightTest, MaterialLightning2)
{
	Material m;
	Tuple position = createPoint(0, 0, 0);
	Tuple eyev = createVector(0, sqrt(2) / 2, -sqrt(2) / 2);
	Tuple normalv = createVector(0, 0, -1);
	Light light(createPoint(0, 0, -10), WHITE);
	Color result = lightning(m, light, position, eyev, normalv);
	ASSERT_EQ(result, createColor(1.0, 1.0, 1.0));
}

TEST(LightTest, MaterialLightning3)
{
	Material m;
	Tuple position = createPoint(0, 0, 0);
	Tuple eyev = createVector(0, 0, -1);
	Tuple normalv = createVector(0, 0, -1);
	Light light(createPoint(0, 10, -10), WHITE);
	Color result = lightning(m, light, position, eyev, normalv);
	ASSERT_EQ(result, createColor(0.7364, 0.7364, 0.7364));
}

TEST(LightTest, MaterialLightning4)
{
	Material m;
	Tuple position = createPoint(0, 0, 0);
	Tuple eyev = createVector(0, -sqrt(2) / 2, -sqrt(2) / 2);
	Tuple normalv = createVector(0, 0, -1);
	Light light(createPoint(0, 10, -10), WHITE);
	Color result = lightning(m, light, position, eyev, normalv);
	ASSERT_EQ(result, createColor(1.6364, 1.6364, 1.6364));
}

TEST(LightTest, MaterialLightning5)
{
	Material m;
	Tuple position = createPoint(0, 0, 0);
	Tuple eyev = createVector(0, 0, -1);
	Tuple normalv = createVector(0, 0, -1);
	Light light(createPoint(0, 0, 10), WHITE);
	Color result = lightning(m, light, position, eyev, normalv);
	ASSERT_EQ(result, createColor(0.1, 0.1, 0.1));
}