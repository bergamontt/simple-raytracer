#include <iostream>
#include <fstream>
#include <numbers>
#include "canvas.h"
#include "transformation.h"
#include "const_colors.h"
#include "world.h"
#include "shapes/plane.h"
#include "patterns/stripe.h"
#include "patterns/checker.h"
#include "patterns/ring.h"
#include "camera.h"
#include "ray.h"

using namespace std;
using namespace std::numbers;

int main(void) {
    ofstream outputFile("test.ppm");

    if (!outputFile.is_open())
        return 1;

    auto floor = make_shared<Plane>();
    Material floorm;
    floorm.color = createColor(1, 0.9, 0.9);

    Solid c1(WHITE);
    Solid c3(createColor(0.8, 0.5, 0.9));
    Solid c2(createColor(0.8, 0.8, 0.9));
    Checker c(&c1, &c2);

    Ring s(&c3, &c1);
    floorm.pattern = &s;

    floorm.specular = 0;
    floor->setMaterial(floorm);

    auto leftWall = make_shared<Plane>();
    leftWall->setTransform(translation(0, 0, 5) *
        rotationY(-pi / 4) *
        rotationX(pi / 2));
    leftWall->setMaterial(floorm);

    auto rightWall = make_shared<Plane>();
    rightWall->setTransform(translation(0, 0, 5) *
        rotationY(pi / 4) *
        rotationX(pi / 2));
    rightWall->setMaterial(floorm);

    auto middle = make_shared<Sphere>();
    middle->setTransform(translation(-0.5, 1, 0.5));
    Material middlem;

    /*Checker c(BLACK, MAGENTA);*/
    //c.setTransform(scaling(0.3, 0.3, 0.3));

    middlem.color = createColor(0.1, 1, 0.5);
    middlem.diffuse = 0.7;
    middlem.specular = 0.3;
    /*middlem.pattern = &c;*/

    middle->setMaterial(middlem);

    auto right = make_shared<Sphere>();
    right->setTransform(translation(0.8, 2, -0.5) *
        scaling(0.5, 0.5, 0.5));
    Material rightm;
    rightm.color = createColor(0.5, 1, 0.1);
    rightm.diffuse = 0.7;
    rightm.specular = 0.3;
    right->setMaterial(rightm);

    auto left = make_shared<Sphere>();
    left->setTransform(translation(-1.5, 0.33, 0.1) *
        scaling(0.33, 0.33, 0.33));
    Material leftm;
    leftm.color = createColor(1, 0.8, 0.1);
    leftm.diffuse = 0.7;
    leftm.specular = 0.3;
    left->setMaterial(leftm);

    World world;
    world.setLight({ createPoint(13, 12, -10), createColor(1, 1, 1) });
    world.addObject(floor);
    world.addObject(leftWall);
    world.addObject(rightWall);
    world.addObject(middle);
    world.addObject(right);
    world.addObject(left);

    Camera camera(200, 100, pi / 3);
    camera.setTransform(viewTransform(createPoint(0, 3, -7),
        createPoint(0, 1, 0),
        createVector(0, 1, 0)));

    Canvas canvas = camera.render(world);

    outputFile << canvas.toPPM();

}