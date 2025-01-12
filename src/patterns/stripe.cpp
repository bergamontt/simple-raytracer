#include "stripe.h"

const Color Stripe::colorAt(const Tuple& point) const
{
    if ((int)(floor(point._x)) % 2 == 0)
        return _fst;
    return _scd;
}

const Color& Stripe::firstColor() const
{
    return _fst;
}

const Color& Stripe::secondColor() const
{
    return _scd;
}
