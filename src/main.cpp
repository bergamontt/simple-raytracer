#include <iostream>
#include <fstream>
#include "canvas.h"
#include "const_colors.h"
#include "ray.h"

using namespace std;

int main(void) {
	ofstream outputFile("test.ppm");

	if (!outputFile.is_open())
		return 1;

	Tuple rayOrigin = createVector(0, 0, -5);

	int canvasSize = 100;
	int wallZ = 10;
	int wallSize = 7;
	float halfWall = wallSize / 2.0;
	float pixelSize = (wallSize * 1.0) / canvasSize;

	Canvas canvas(canvasSize, canvasSize);
	Color ballColor = RED;
	Sphere sphere;

	for (int y = 0; y < canvasSize; ++y)
	{
		float worldY = halfWall - pixelSize * y;
		for (int x = 0; x < canvasSize; ++x)
		{
			float worldX = -halfWall + pixelSize * x;
			
			Tuple position = createPoint(worldX, worldY, wallZ);
			Ray ray(rayOrigin, normalize((position - rayOrigin)));
			
			optional<Intersections> xs = ray.intersect(sphere);
			if (xs.has_value())
				canvas.writePixel(x, y, ballColor);
		}
	}

	outputFile << canvas.toPPM();

}