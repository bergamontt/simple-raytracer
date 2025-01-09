#include "intersection.h"

float Intersection::time() const
{
    return _time;
}

const ShapeConstPtr& Intersection::object() const
{
    return _object;
}

bool operator>(const Intersection& a, const Intersection& b)
{
    return a.time() > b.time();
}

bool operator<(const Intersection& a, const Intersection& b)
{
    return a.time() < b.time();
}

bool operator==(const Intersection& a, const Intersection& b)
{
    return a.object() == b.object() && a.time() == b.time();
}

bool operator!=(const Intersection& a, const Intersection& b)
{
    return !(a == b);
}
