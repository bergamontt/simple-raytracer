#include "ring.h"

const Color Ring::colorAt(const Tuple& point) const
{
    float distance = sqrt(point._x * point._x + point._z * point._z);
    int distanceFloor = static_cast<int>(floor(distance));
    if (distanceFloor % 2 == 0)
        return _fst->colorAt(point);
    return _scd->colorAt(point);
}