#include "gtest/gtest.h"
#include "stripe.h"
#include "../material.h"
#include "../light.h"
#include "../shapes/sphere.h"
#include "../lightning.h"
#include "../transformation.h"

TEST(StripeTest, DefaultStripePattern)
{
	Stripe s;
	ASSERT_EQ(s.firstColor(), WHITE);
	ASSERT_EQ(s.secondColor(), BLACK);
}

TEST(StripeTest, StripeColorAt1)
{
	Stripe s;
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0, 1, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0, 2, 0)), WHITE);
}

TEST(StripeTest, StripeColorAt2)
{
	Stripe s;
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 1)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 2)), WHITE);
}

TEST(StripeTest, StripeColorAt3)
{
	Stripe s;
	ASSERT_EQ(s.colorAt(createPoint(0, 0, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(0.9, 0, 0)), WHITE);
	ASSERT_EQ(s.colorAt(createPoint(1, 2, 0)), BLACK);
	ASSERT_EQ(s.colorAt(createPoint(-0.1, 0, 0)), BLACK);
	ASSERT_EQ(s.colorAt(createPoint(-1, 0, 0)), BLACK);
	ASSERT_EQ(s.colorAt(createPoint(-1.1, 0, 0)), WHITE);
}

TEST(StripeTest, StripeAtMaterial)
{
	Stripe stripe;
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

	Stripe stripe;
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

	Stripe stripe;
	Material m = s.material();
	m.pattern = &stripe;
	s.setMaterial(m);

	Color res = s.patternColorAt(createPoint(1.5, 0, 0));
	ASSERT_EQ(res, WHITE);
}

TEST(StripeTest, StripesWithObjectTransformation2)
{
	Sphere s;

	Stripe stripe;
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

	Stripe stripe;
	stripe.setTransform(translation(0.5, 0, 0));
	Material m = s.material();
	m.pattern = &stripe;
	s.setMaterial(m);

	Color res = s.patternColorAt(createPoint(2.5, 0, 0));
	ASSERT_EQ(res, WHITE);
}