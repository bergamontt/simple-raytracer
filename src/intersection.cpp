#include "intersection.h"

float Intersection::time() const
{
    return _time;
}

const Sphere Intersection::object() const
{
    return _sphere;
}

bool operator>(const Intersection& a, const Intersection& b)
{
    return a.object() == b.object() && a.time() > b.time();
}

bool operator<(const Intersection& a, const Intersection& b)
{
    return a.object() == b.object() && a.time() < b.time();
}

bool operator==(const Intersection& a, const Intersection& b)
{
    return a.object() == b.object() && a.time() == b.time();
}

bool operator!=(const Intersection& a, const Intersection& b)
{
    return !(a == b);
}
