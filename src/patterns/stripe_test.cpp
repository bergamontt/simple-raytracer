#include "gtest/gtest.h"
#include "stripe.h"
#include "gradient.h"
#include "ring.h"
#include "checker.h"
#include "solid.h"
#include "../material.h"
#include "../light.h"
#include "../shapes/sphere.h"
#include "../lightning.h"
#include "../transformation.h"

TEST(StripeTest, StripeColorAt1)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Stripe s(&s1, &s2);
	
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0, 1, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0, 2, 0)), WHITE);
}

TEST(StripeTest, StripeColorAt2)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Stripe s(&s1, &s2);
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 1)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 2)), WHITE);
}

TEST(StripeTest, StripeColorAt3)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Stripe s(&s1, &s2);
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0.9, 0, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(1, 2, 0)), BLACK);
	ASSERT_EQ(s.colorAt(createPoint(-0.1, 0, 0)), BLACK);
	ASSERT_EQ(s.colorAt(createPoint(-1, 0, 0)), BLACK);
	ASSERT_EQ(s.colorAt(createPoint(-1.1, 0, 0)), WHITE);
}

TEST(StripeTest, StripeAtMaterial)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Stripe stripe(&s1, &s2);
	Material m = { WHITE, 1, 0, 0, 200, &stripe };
	Tuple eyev = createVector(0, 0, -1);
	Tuple normalv = createVector(0, 0, -1);
	Light light(createPoint(0, 0, -10), WHITE);

	Color c1 = lightning(m, nullptr, light, createPoint(0.9, 0, 0), eyev, normalv, false);
	Color c2 = lightning(m, nullptr, light, createPoint(1.1, 0, 0), eyev, normalv, false);

	ASSERT_EQ(c1, WHITE);
	ASSERT_EQ(c2, BLACK);
}

TEST(StripeTest, StripesWithObjectTransformation)
{
	Sphere s;
	s.setTransform(scaling(2, 2, 2));

	Solid s1(WHITE);
	Solid s2(BLACK);
	Stripe stripe(&s1, &s2);
	Material m = s.material();
	m.pattern = &stripe;
	s.setMaterial(m);

	Color res = s.patternColorAt(createPoint(1.5, 0, 0));
	ASSERT_EQ(res, WHITE);
}

TEST(StripeTest, StripesWithObjectTransformation1)
{
	Sphere s;
	s.setTransform(scaling(2, 2, 2));

	Solid s1(WHITE);
	Solid s2(BLACK);
	Stripe stripe(&s1, &s2);
	Material m = s.material();
	m.pattern = &stripe;
	s.setMaterial(m);

	Color res = s.patternColorAt(createPoint(1.5, 0, 0));
	ASSERT_EQ(res, WHITE);
}

TEST(StripeTest, StripesWithObjectTransformation2)
{
	Sphere s;

	Solid s1(WHITE);
	Solid s2(BLACK);
	Stripe stripe(&s1, &s2);
	stripe.setTransform(scaling(2, 2, 2));

	Material m = s.material();
	m.pattern = &stripe;
	s.setMaterial(m);

	Color res = s.patternColorAt(createPoint(1.5, 0, 0));
	ASSERT_EQ(res, WHITE);
}

TEST(StripeTest, StripesWithObjectTransformation3)
{
	Sphere s;
	s.setTransform(scaling(2, 2, 2));

	Solid s1(WHITE);
	Solid s2(BLACK);
	Stripe stripe(&s1, &s2);
	stripe.setTransform(translation(0.5, 0, 0));
	Material m = s.material();
	m.pattern = &stripe;
	s.setMaterial(m);

	Color res = s.patternColorAt(createPoint(2.5, 0, 0));
	ASSERT_EQ(res, WHITE);
}

TEST(GradientTest, GradientLinearlyInterpolatesBetweenColors)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Gradient g(&s1, &s2);
	ASSERT_EQ(g.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(g.colorAt(createPoint(0.25, 0, 0)), createColor(0.75, 0.75, 0.75));
	ASSERT_EQ(g.colorAt(createPoint(0.5, 0, 0)), createColor(0.5, 0.5, 0.5));
	ASSERT_EQ(g.colorAt(createPoint(0.75, 0, 0)), createColor(0.25, 0.25, 0.25));
}

TEST(RingTest, RingColorTest)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Ring g(&s1, &s2);
	ASSERT_EQ(g.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(g.colorAt(createPoint(1, 0, 0)), BLACK);
	ASSERT_EQ(g.colorAt(createPoint(0, 0, 1)), BLACK);
	ASSERT_EQ(g.colorAt(createPoint(0.708, 0, 0.708)), BLACK);
}

TEST(CheckerTest, CheckerColorTestX)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Checker c(&s1, &s2);
	ASSERT_EQ(c.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(c.colorAt(createPoint(0.99, 0, 0)), WHITE);
	ASSERT_EQ(c.colorAt(createPoint(1.01, 0, 0)), BLACK);
}

TEST(CheckerTest, CheckerColorTestY)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Checker c(&s1, &s2);
	ASSERT_EQ(c.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(c.colorAt(createPoint(0, 0.99, 0)), WHITE);
	ASSERT_EQ(c.colorAt(createPoint(0, 1.01, 0)), BLACK);
}

TEST(CheckerTest, CheckerColorTestZ)
{
	Solid s1(WHITE);
	Solid s2(BLACK);
	Checker c(&s1, &s2);
	ASSERT_EQ(c.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(c.colorAt(createPoint(0, 0, 0.99)), WHITE);
	ASSERT_EQ(c.colorAt(createPoint(0, 0, 1.01)), BLACK);
}