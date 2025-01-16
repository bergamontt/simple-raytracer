#include "sphere.h"
#include "../refractive_indexes.h"
#include "../intersections.h"
#include "../ray.h"


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

optional<Intersections> Sphere::localIntersection(const Ray& transformedRay) const
{
    Tuple sphereToRay = transformedRay.origin() - _origin;

    float a = dot(transformedRay.direction(), transformedRay.direction());
    float b = 2 * dot(transformedRay.direction(), sphereToRay);
    float c = dot(sphereToRay, sphereToRay) - 1;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return {};

    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    Intersections intersections;

    if (t1 > t2)
    {
        intersections.add({ t2 , shared_from_this() });
        intersections.add({ t1 , shared_from_this() });
    }
    else {
        intersections.add({ t1 , shared_from_this() });
        intersections.add({ t2 , shared_from_this() });
    }

    return intersections;
}

const Sphere Sphere::glassSphere()
{
    Sphere glassSphere;
    Material glass = glassSphere.material();
    glass.transparency = 1.0f;
    glass.reflactiveIndex = GLASS;
    glassSphere.setMaterial(glass);
    return glassSphere;
}

const Tuple Sphere::localNormal(const Tuple& point) const
{
    return normalize(point - _origin);
}

bool operator==(const Sphere& a, const Sphere& b)
{
    return a.id() == b.id();
}