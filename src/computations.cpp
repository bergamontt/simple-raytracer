#include "computations.h"
#include <vector>

float Computations::time() const
{
    return _time;
}

float Computations::n1() const
{
    return _n1;
}

float Computations::n2() const
{
    return _n2;
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

const Tuple& Computations::underPoint() const
{
    return _underPoint;
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

void Computations::calculateUnderPoint()
{
    _underPoint = _point - _normalVector * EPSILON;
}

void Computations::calculateDefaultIndeces(const Intersection& intrs)
{
    Intersections xs;
    xs.add(intrs);
    calculateIndeces(intrs, xs);
}

void Computations::calculateIndeces(const Intersection& hit, const Intersections& xs)
{
    vector<ShapeConstPtr> containers;
    for (int i = 0; i < xs.size(); ++i)
    {
        Intersection currIntrs = xs.get(i);
        if (currIntrs == hit)
        {
            if (containers.empty())
                _n1 = 1.0f;
            else _n1 = containers.back()->material().reflactiveIndex;
        }
        
        bool included = false;
        const ShapeConstPtr& currShape = currIntrs.object();
        for (int i = 0; i < containers.size(); ++i)
        {
            const ShapeConstPtr& shape = containers.at(i);
            if (currShape == shape)
            {
                containers.erase(containers.begin() + i);
                included = true;
                break;
            } 
        }

        if (!included)
            containers.emplace_back(currShape);

        if (currIntrs == hit)
        {
            if (containers.empty())
                _n2 = 1.0f;
            else _n2 = containers.back()->material().reflactiveIndex;
        }
    }
}