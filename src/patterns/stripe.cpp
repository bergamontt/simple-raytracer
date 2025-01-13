#include "stripe.h"

const Color Stripe::colorAt(const Tuple& point) const
{
    if ((int)(floor(point._x)) % 2 == 0)
        return _fst->colorAt(point);
    return _scd->colorAt(point);
}