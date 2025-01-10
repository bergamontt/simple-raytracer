#pragma once
#include "color.h"
#include <sstream>

using namespace std;

class Canvas
{
public:

	Canvas(int width, int height)
		: _width { width }
		, _height{ height }
		, _pixels{ new Color[width * height]{} }
	{}

	Canvas(const Canvas& src)
	{
		deepCopy(src);
	}

	~Canvas();

	Canvas& operator=(const Canvas& src);

	const Color& pixelAt(int x, int y);
	void writePixel(int x, int y, const Color& color);

	string toPPM();

	int width() const;
	int height() const;

private:

	int _width;
	int _height;
	Color* _pixels;

	int indexOf(int x, int y) const;

	void appendHeaderPPM(ostream& ss) const;
	void appendPixelsPPM(ostream& ss) const;

	void deepCopy(const Canvas& src);
};

