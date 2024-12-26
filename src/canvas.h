#pragma once

#include "color.h"
#include <sstream>

class Canvas {
public:

	Canvas(int width, int height)
		: _width { width }
		, _height{ height }
		, _pixels{ new Color[width * height]{} }
	{}

	~Canvas();

	const Color pixelAt(int x, int y);
	void writePixel(int x, int y, const Color& color);
	
	std::string toPPM();

	int width() const;
	int height() const;

private:

	int _width;
	int _height;
	Color* _pixels;

	int indexOf(int x, int y) const;

	void appendHeaderPPM(std::ostream& ss) const;
	void appendPixelsPPM(std::ostream& ss) const;

};

