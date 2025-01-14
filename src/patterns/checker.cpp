#include "checker.h"

const Color Checker::colorAt(const Tuple& p) const
{
    int dimensionSum = (int)floor(p._x) + (int)floor(p._y) + (int)floor(p._z);
    if (dimensionSum % 2 == 0)
        return _fst->colorAt(p);
    return _scd->colorAt(p);
}