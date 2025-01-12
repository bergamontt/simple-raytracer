#pragma once
#include <memory>

using namespace std;

class Shape;

using ShapePtr = shared_ptr<Shape>;
using ShapeConstPtr = shared_ptr<const Shape>;

class Pattern;

using PatternPtr = shared_ptr<Pattern>;
using PatternConstPtr = shared_ptr<const Pattern>;