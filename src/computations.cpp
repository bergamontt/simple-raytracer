#include "computations.h"

float Computations::time() const
{
    return _time;
}

const ShapeConstPtr& Computations::object() const
{
    return _object;
}

const Tuple& Computations::point() const
{
    return _point;
}

const Tuple& Computations::eyeVector() const
{
    return _eyeVector;
}

const Tuple& Computations::normalVector() const
{
    return _normalVector;
}

const Tuple& Computations::overPoint() const
{
    return _overPoint;
}

const Tuple& Computations::reflectVector() const
{
    return _reflectVector;
}

bool Computations::inside() const
{
    return _inside;
}

void Computations::calculateVectors()
{
    _point = _ray.position(_time);
    _eyeVector = -_ray.direction();
    _normalVector = _object->normalAt(_point);
    _reflectVector = reflect(_ray.direction(),_normalVector);
}

void Computations::negateIfInside()
{
    if (dot(_normalVector, _eyeVector) < 0.0f)
    {
        _inside = true;
        _normalVector = -_normalVector;
    }
}

void Computations::calculateOverPoint()
{
    _overPoint = _point + _normalVector * EPSILON;
}
