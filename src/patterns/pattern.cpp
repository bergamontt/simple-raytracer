#include "pattern.h"

const Matrix& Pattern::transform() const
{
    return _transform;
}

void Pattern::setTransform(const Matrix& transform)
{
    _transform = transform;
}
