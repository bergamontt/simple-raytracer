#include "checker.h"

const Color Checker::colorAt(const Tuple& p) const
{
    int dimensionSum = floor(p._x) + floor(p._y) + floor(p._z);
    if (dimensionSum % 2 == 0)
        return _fst->colorAt(p);
    return _scd->colorAt(p);
}