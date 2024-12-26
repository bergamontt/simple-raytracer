#include "gtest/gtest.h"
#include "canvas.h"
#include "const_colors.h"

TEST(CanvasTest, CanvasCreation) {
	Canvas canvas(10, 20);
	ASSERT_EQ(canvas.width(), 10);
	ASSERT_EQ(canvas.height(), 20);
}

TEST(CanvasTest, CanvasPixelAt) {
	Canvas canvas(10, 20);
	for (int i = 0; i < canvas.width(); ++i) {
		for (int j = 0; j < canvas.height(); ++j)
			ASSERT_EQ(canvas.pixelAt(i, j), BLACK);
	}
}

TEST(CanvasTest, CanvasWritePixel) {

}