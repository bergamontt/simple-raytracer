#include "light.h"

const Tuple Light::position() const
{
    return _position;
}

const Color Light::intensity() const
{
    return _intensity;
}
