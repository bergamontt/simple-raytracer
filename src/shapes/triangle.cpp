#include "triangle.h"

const Tuple& Triangle::fstPoint() const
{
    return _p1;
}

const Tuple& Triangle::scdPoint() const
{
    return _p2;
}

const Tuple& Triangle::trdPoint() const
{
    return _p3;
}

const Tuple& Triangle::fstEdgeVector() const
{
    return _e1;
}

const Tuple& Triangle::scdEdgeVector() const
{
    return _e2;
}

optional<Intersections> Triangle::localIntersection(const Ray& ray) const
{
    const Tuple& rayDirection = ray.direction();

    Tuple dirCrossE2 = cross(rayDirection, scdEdgeVector());
    float determinant = dot(fstEdgeVector(), dirCrossE2);
    if (fabs(determinant) < EPSILON)
        return {};
    
    const Tuple& rayOrigin = ray.origin();
    
    float f = 1.0f / determinant;
    Tuple p1ToOrigin = rayOrigin - fstPoint();
    float u = f * dot(p1ToOrigin, dirCrossE2);
    if (u < 0.0f || u > 1.0f)
        return {};

    Tuple originCrossE1 = cross(p1ToOrigin, fstEdgeVector());
    float v = f * dot(rayDirection, originCrossE1);
    if (v < 0.0f || (u + v) > 1.0f)
        return {};

    float time = f * dot(scdEdgeVector(), originCrossE1);
    Intersections xs;
    xs.add({time, shared_from_this()});
    return xs;
}

const Tuple Triangle::localNormal(const Tuple& point) const
{
    return _normal;
}
