#include "camera.h"
#include <cmath>

const Canvas Camera::render(const World& w)
{
    Canvas image(_hsize, _vsize);
    for (int y = 0; y < _vsize; ++y)
    {
        for (int x = 0; x < _hsize; ++x)
        {
            Ray ray = rayForPixel(x, y);
            Color color = w.colorAt(ray);
            image.writePixel(x, y, color);
        }
    }
    return image;
}

const Ray Camera::rayForPixel(int px, int py) const
{
    float pcOffset = 0.5;

    float xOffset = (px + pcOffset) * _pixelSize;
    float yOffset = (py + pcOffset) * _pixelSize;

    float worldX = _halfWidth - xOffset;
    float worldY = _halfHeight - yOffset;

    Tuple pixel = _transform.inverse() * createPoint(worldX, worldY, -1);
    Tuple origin = _transform.inverse() * createPoint(0, 0, 0);
    Tuple direction = normalize(pixel - origin);
    
    return { origin, direction };
}

int Camera::hsize() const
{
    return _hsize;
}

int Camera::vsize() const
{
    return _vsize;
}

float Camera::fieldOfView() const
{
    return _fieldOfView;
}

float Camera::pixelSize() const
{
    return _pixelSize;
}

void Camera::setTransform(const Matrix& m)
{
    if (m.rows() == TRANSFORM_N
      && m.columns() == TRANSFORM_N)
        _transform = m;
}

void Camera::calculateHalfSize()
{
    float halfView = tan(_fieldOfView / 2);
    float aspectRatio = (_hsize * 1.0) / _vsize;

    if (aspectRatio >= 1)
    {
        _halfWidth = halfView;
        _halfHeight = halfView / aspectRatio;
    }
    else
    {
        _halfWidth = halfView * aspectRatio;
        _halfHeight = halfView;
    }
}

void Camera::calculatePixelSize()
{
    _pixelSize = (_halfWidth * 2) / _hsize;
}

void Camera::calculateHalfAndPixelSize()
{
    calculateHalfSize();
    calculatePixelSize();
}
