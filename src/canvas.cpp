#include "canvas.h"
#include "constants.h"
#include "color.h"

Canvas::~Canvas()
{
    delete[] _pixels;
    _pixels = nullptr;
    _width = 0;
    _height = 0;
}

Canvas& Canvas::operator=(const Canvas& src)
{
    if (this != &src)
        deepCopy(src);
    return *this;
}

const Color Canvas::pixelAt(int x, int y)
{
    return _pixels[indexOf(x, y)];
}

void Canvas::writePixel(int x, int y, const Color& color)
{
    _pixels[indexOf(x, y)] = color;
}

std::string Canvas::toPPM()
{
    std::ostringstream ss;
    appendHeaderPPM(ss);
    appendPixelsPPM(ss);
    return ss.str();
}

int Canvas::width() const
{
    return _width;
}

int Canvas::height() const
{
    return _height;
}

int Canvas::indexOf(int x, int y) const
{
    return x + y * _width;
}

void Canvas::appendHeaderPPM(std::ostream& ss) const
{
    ss << "P3\n" << _width << " " << _height << "\n255\n";
}

void Canvas::appendPixelsPPM(std::ostream& ss) const
{
    int pixelsCount = 0;
    for (int i = 0; i < _height * _width; ++i, ++pixelsCount) {
        ss << pixelToPPM(_pixels[i]);
        if (pixelsCount == PIXELS_PER_LINE)
            ss << '\n';
        else ss << ' ';
    }

    if (pixelsCount != PIXELS_PER_LINE)
        ss << '\n';
}

void Canvas::deepCopy(const Canvas& src)
{
    _width = src._width;
    _height = src._height;

    int n = _width * _height;
    _pixels = new Color[n]();

    for (int i = 0; i < n; ++i)
        _pixels[i] = src._pixels[i];
}
