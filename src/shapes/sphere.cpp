#include "sphere.h"
#include "../func.h"

const Tuple Sphere::normalAt(const Tuple& point) const
{
    Matrix transformInverse = _transform.inverse();
    Tuple objectPoint = transformInverse * point;
    Tuple objectNormal = normalize(objectPoint - _origin);
    Tuple worldNormal = transformInverse.transpose() * objectNormal;
    worldNormal._w = 0;
    return normalize(worldNormal);
}

const Material Sphere::material() const
{
    return _material;
}

const Matrix Sphere::transform() const
{
    return _transform;
}

void Sphere::setTransform(const Matrix& m)
{
    _transform = m;
}

void Sphere::setMaterial(const Material& m)
{
    _material = m;
}

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
