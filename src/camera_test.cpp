#include <numbers>
#include "gtest/gtest.h"
#include "transformation.h"
#include "camera.h"
#include "world.h"
#include "canvas.h"

using namespace std::numbers;

TEST(CameraTest, ConstructingCamera)
{
	int hsize = 160;
	int vsize = 120;
	float fieldOfView = pi / 2;

	Camera c(hsize, vsize, fieldOfView);

	ASSERT_EQ(c.hsize(), hsize);
	ASSERT_EQ(c.vsize(), vsize);
	ASSERT_FLOAT_EQ(c.fieldOfView(), fieldOfView);
}

TEST(CameraTest, PixelSizeForHorizontalCanvas)
{
	int hsize = 200;
	int vsize = 125;
	float fieldOfView = pi / 2;

	Camera c(hsize, vsize, fieldOfView);

	ASSERT_FLOAT_EQ(c.pixelSize(), 0.01);
}

TEST(CameraTest, PixelSizeForVerticalCanvas)
{
	int hsize = 125;
	int vsize = 200;
	float fieldOfView = pi / 2;

	Camera c(hsize, vsize, fieldOfView);

	ASSERT_FLOAT_EQ(c.pixelSize(), 0.01);
}

TEST(CameraTest, RayThroughCanvasCenter)
{
	int hsize = 201;
	int vsize = 101;
	float fieldOfView = pi / 2;

	Camera c(hsize, vsize, fieldOfView);

	Ray r = c.rayForPixel(100, 50);
	ASSERT_EQ(r.origin(), createPoint(0, 0, 0));
	ASSERT_EQ(r.direction(), createVector(0, 0, -1));
}

TEST(CameraTest, RayThroughCanvasCorner)
{
	int hsize = 201;
	int vsize = 101;
	float fieldOfView = pi / 2;

	Camera c(hsize, vsize, fieldOfView);

	Ray r = c.rayForPixel(0, 0);
	ASSERT_EQ(r.origin(), createPoint(0, 0, 0));
	ASSERT_EQ(r.direction(), createVector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTest, RayWithCameraTransformed)
{
	int hsize = 201;
	int vsize = 101;
	float fieldOfView = pi / 2;

	Camera c(hsize, vsize, fieldOfView);
	c.setTransform(rotationY(pi / 4) * translation(0, -2, 5));;

	Ray r = c.rayForPixel(100, 50);
	ASSERT_EQ(r.origin(), createPoint(0, 2, -5));
	ASSERT_EQ(r.direction(), createVector(sqrt(2) / 2, 0, -sqrt(2) / 2));
}

TEST(CameraTest, RenderingWorldWithCamera)
{
	World w = World::defaultWorld();
	Camera c(11, 11, pi / 2);
	
	Tuple from = createPoint(0, 0, -5);
	Tuple to = createPoint(0, 0, 0);
	Tuple up = createVector(0, 1, 0);

	c.setTransform(viewTransform(from, to, up));
	Canvas image(c.render(w));
	ASSERT_EQ(image.pixelAt(5, 5), createColor(0.38066, 0.47583, 0.2855));
}