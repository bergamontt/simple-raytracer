#include "canvas.h"

Canvas::~Canvas() {
    delete[] _pixels;
    _pixels = nullptr;
    _width = 0;
    _height = 0;
}

const Color Canvas::pixelAt(int x, int y) {
    return _pixels[indexOf(x, y)];
}

void Canvas::writePixel(int x, int y, const Color& color) {
    _pixels[indexOf(x, y)] = color;
}

int Canvas::width() const {
    return _width;
}

int Canvas::height() const {
    return _height;
}

int Canvas::indexOf(int x, int y) const
{
    return x + y * _width;
}
