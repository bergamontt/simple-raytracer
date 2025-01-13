#include "gradient.h"

const Color Gradient::colorAt(const Tuple& point) const
{
    Color distance = _scd->colorAt(point) - _fst->colorAt(point);
    float fraction = point._x - floor(point._x);
    return _fst->colorAt(point) + distance * fraction;
}