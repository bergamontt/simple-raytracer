#include "plane.h"

optional<Intersections> Plane::localIntersection(const Ray& ray) const
{
    if (fabs(ray.direction()._y) < EPSILON)
        return {};
    Intersections intersections;
    float intersecionTime = -ray.origin()._y / ray.direction()._y;
    intersections.add({intersecionTime, shared_from_this() });
    return intersections;
}

const Tuple Plane::localNormal(const Tuple& point) const
{
    return createVector(0, 1, 0);
}
