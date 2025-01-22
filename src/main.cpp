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
#include "shapes/cube.h"
#include "refractive_indexes.h"

using namespace std;
using namespace std::numbers;

int main(void) {
    ofstream outputFile("test.ppm");

    if (!outputFile.is_open())
        return 1;

    auto floor = make_shared<Plane>();
    Material floorm;
    /*floorm.color = createColor(1, 0.9, 0.9);*/
    floorm.color = createColor(0.1, 0.1, 0.1);

    //Solid c1(WHITE);
    //Solid c3(createColor(0.8, 0.5, 0.9));
    //Solid c2(createColor(0.8, 0.8, 0.9));
    //Checker c(&c1, &c2);

   /* Ring s(&c3, &c1);
    floorm.pattern = &s;*/

    Solid s1(BLACK);
    Solid s2(MAGENTA);
    Stripe cc(&s1, &s2);
    cc.setTransform(scaling(0.7, 0.7, 0.7));
   /* floorm.pattern = &cc;*/
    floorm.reflective = 0.7;

    Material floorm2;
    floorm2.color = BLUE;
    floorm2.pattern = &cc;
    floorm2.reflective = 0.9f;
    /*floorm2.reflactiveIndex = GLASS;*/
    floorm2.transparency = 1.0f;
    floorm2.diffuse = 0.6f;
    floorm2.shininess = 300.0f;

    floorm.specular = 0.5;
    floor->setMaterial(floorm2);

    auto leftWall = make_shared<Plane>();
    leftWall->setTransform(translation(2, 0, 10) *
        rotationY(-pi / 4) *
        rotationX(pi / 2));
    leftWall->setMaterial(floorm2);

    auto rightWall = make_shared<Plane>();
    rightWall->setTransform(translation(0, 0, 5) *
        rotationY(pi / 4) *
        rotationX(pi / 2));
    rightWall->setMaterial(floorm2);

    /*Sphere glass = Sphere::glassSphere();*/
    auto middle = make_shared<Sphere>();
    middle->setTransform(translation(-0.5, 1, 0.5));
    Material middlem;

    middlem.color = createColor(0.9, 0.9, 0.9);
    middlem.diffuse = 0.2f;
    middlem.specular = 0.5f;
    middlem.reflective = 0.72f;
    middlem.transparency = 1.0f;
    middlem.shininess = 0.4f;
    middlem.reflactiveIndex = GLASS;
   /* middlem.pattern = &cc;*/

    middle->setMaterial(middlem);

    auto right = make_shared<Sphere>();
    right->setTransform(translation(0.8, 2, -0.5) *
        scaling(0.5, 0.5, 0.5));
    Material rightm;
    rightm.color = createColor(0.5, 1, 0.1);
    rightm.diffuse = 0.7;
    rightm.specular = 0.3;
    rightm.reflective = 0.2;
    right->setMaterial(rightm);

    auto left = make_shared<Sphere>();
    left->setTransform(translation(-1.5, 0.33, 0.1) *
        scaling(0.33, 0.33, 0.33));
    Material leftm;
    leftm.color = WHITE;
    leftm.diffuse = 0.7;
    leftm.specular = 0.3;
    leftm.shininess = 1.0f;
    leftm.reflective = 0.2;
    left->setMaterial(leftm);

    /////

    Cube s4;
    auto ss4 = make_shared<Cube>(s4);
    ss4->material().reflective = 1;
    ss4->material().diffuse = 0.2f;
    ss4->material().ambient = 0.1f;
    ss4->material().specular = 1.0f;
    ss4->material().shininess = 600.0f;
    ss4->material().reflactiveIndex = GLASS;
    ss4->setTransform(scaling(1.5, 1.5, 1.5) * translation(0, 1, 0));

    Sphere s5 = Sphere::glassSphere();
    auto ss5 = make_shared<Sphere>(s5);
    ss5->material().reflective = 0.9;
    ss5->material().diffuse = 0.3f;
    ss5->material().specular = 1.0f;
    ss5->material().shininess = 600.0f;
    ss5->material().reflactiveIndex = GLASS;
    ss5->material().color = createColor(0, 0.5, 0);
    ss5->setTransform(scaling(1.5, 1.5, 1.5) * translation(1.5, 1, -2.5));

    Sphere s6 = Sphere::glassSphere();
    auto ss6 = make_shared<Sphere>(s6);
    ss6->material().reflective = 0.9;
    ss6->material().diffuse = 0.1f;
    ss6->material().specular = 1.0f;
    ss6->material().shininess = 600.0f;
    ss6->material().reflactiveIndex = GLASS;
    ss6->material().color = createColor(0.5, 0, 0);
    ss6->setTransform(translation(2.4, 1, 2.4));

    World world;
    world.setLight({ createPoint(6, 5, -10), createColor(1, 1, 1) });
   
    world.addObject(ss4);
    world.addObject(ss5);
    world.addObject(ss6);
    world.addObject(floor);

    world.addObject(leftWall);
    /*world.addObject(rightWall);*/
    /*world.addObject(middle);*/
    /*world.addObject(right);
    world.addObject(left);*/

    Camera camera(1200, 600, pi / 3.5);
    camera.setTransform(viewTransform(createPoint(10, 8, -3),
        createPoint(0, 1, 0),
        createVector(0, 1, 0)));

    Canvas canvas = camera.render(world);

    outputFile << canvas.toPPM();

}