#pragma once
#include <memory>

using namespace std;

class Shape;

using ShapePtr = shared_ptr<Shape>;
using ShapeConstPtr = shared_ptr<const Shape>;