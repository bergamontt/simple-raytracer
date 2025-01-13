#include "solid.h"

const Color Solid::colorAt(const Tuple& point) const
{
    return _color;
}

const Color& Solid::baseColor() const
{
    return _color;
}
