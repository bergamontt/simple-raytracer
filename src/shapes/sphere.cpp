#include "sphere.h"
#include "../func.h"

const Tuple Sphere::origin() const
{
    return _origin;
}

const float Sphere::radius() const
{
    return _radius;
}

const int Sphere::id() const
{
    return _thisID;
}

bool operator==(const Sphere& a, const Sphere& b)
{
    return a.id() == b.id();
}
