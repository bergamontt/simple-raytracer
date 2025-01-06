#include <iostream>
#include <fstream>
#include <numbers>
#include "canvas.h"
#include "transformation.h"
#include "const_colors.h"
#include "world.h"
#include "camera.h"
#include "ray.h"

using namespace std;
using namespace std::numbers;

int main(void) {
	ofstream outputFile("test.ppm");

	if (!outputFile.is_open())
		return 1;

	Sphere floor;
	floor.setTransform(scaling(10, 0.01, 10));
	Material floorm;
	floorm.color = createColor(1, 0.9, 0.9);
	floorm.specular = 0;
	floor.setMaterial(floorm);

	Sphere leftWall;
	leftWall.setTransform(translation(0, 0, 5) *
						 rotationY(-pi / 4) *
						 rotationX(pi / 2) *
						 scaling(10, 0.01, 10));
	leftWall.setMaterial(floorm);
	
	Sphere rightWall;
	rightWall.setTransform(translation(0, 0, 5) *
						   rotationY(pi / 4) *
						   rotationX(pi / 2) *
						   scaling(10, 0.01, 10));
	rightWall.setMaterial(floorm);

	Sphere middle;
	middle.setTransform(translation(-0.5, 1, 0.5));
	Material middlem;
	middlem.color = createColor(0.1, 1, 0.5);
	middlem.diffuse = 0.7;
	middlem.specular = 0.3;
	middle.setMaterial(middlem);

	Sphere right;
	right.setTransform(translation(0.6, 2.2, -0.8) *
				       scaling(0.5, 0.5, 0.5));
	Material rightm;
	rightm.color = createColor(0.5, 1, 0.1);
	rightm.diffuse = 0.7;
	rightm.specular = 0.3;
	right.setMaterial(rightm);

	Sphere left;
	left.setTransform(translation(0.25, 1.5, -0.5) *
					  scaling(0.25, 0.25, 0.25));
	Material leftm;
	leftm.color = createColor(1, 0.8, 0.1);
	leftm.diffuse = 0.7;
	leftm.specular = 0.3;
	left.setMaterial(leftm);

	World world;
	world.setLight({createPoint(13, 12, -10), createColor(1, 1, 1)});
	world.addObject(floor);
	world.addObject(leftWall);
	world.addObject(rightWall);
	world.addObject(middle);
	world.addObject(right);
	world.addObject(left);

	Camera camera(1000, 500, pi / 3);
	camera.setTransform(viewTransform(createPoint(-3, 3, -6),
									  createPoint(0, 1, 0),
									  createVector(0, 1, 0)));

	Canvas canvas = camera.render(world);

	outputFile << canvas.toPPM();

}