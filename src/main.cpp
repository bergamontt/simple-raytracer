#include <iostream>
#include <fstream>
#include "canvas.h"
#include "transformation.h"
#include "const_colors.h"
#include "ray.h"

using namespace std;

int main(void) {
	ofstream outputFile("test.ppm");

	if (!outputFile.is_open())
		return 1;

	Tuple rayOrigin = createVector(0, 0, -5);

	int canvasSize = 500;
	int wallZ = 10;
	int wallSize = 7;
	float halfWall = wallSize / 2.0;
	float pixelSize = (wallSize * 1.0) / canvasSize;

	Canvas canvas(canvasSize, canvasSize);
	
	Material material;
	material.color = createColor(0.9, 0.2, 0);

	Material m1;
	m1.color = createColor(0.9, 0.2, 0);

	Tuple lightPosition = createPoint(-10, 10, -10);
	Color lightColor = createColor(1, 0.2, 1);
	Light light(lightPosition, lightColor);

	Sphere sphere;
	sphere.setTransform(scaling(1, 0.3, 1));
	sphere.setMaterial(material);


	for (int y = 0; y < canvasSize; ++y)
	{
		float worldY = halfWall - pixelSize * y;
		for (int x = 0; x < canvasSize; ++x)
		{
			float worldX = -halfWall + pixelSize * x;
			
			Tuple position = createPoint(worldX, worldY, wallZ);
			Ray ray(rayOrigin, normalize((position - rayOrigin)));

			optional<Intersections> xs  = ray.intersect(sphere);

			if (xs.has_value())
			{
				Intersections intersections = xs.value();
				optional<Intersection> xh = intersections.hit();
				if (xh.has_value())
				{
					Intersection hit = xh.value();
					Tuple point = ray.position(hit.time());
					Tuple normal = sphere.normalAt(point);
					Tuple eye = -ray.direction();
					Color ballColor = lightning(sphere.material(), light, point, eye, normal);
					canvas.writePixel(x, y, ballColor);
				}
			}

		}
	}

	outputFile << canvas.toPPM();

}