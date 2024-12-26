#pragma once

#include "color.h"

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

	int width() const;
	int height() const;

private:

	int _width;
	int _height;
	Color* _pixels;

	int indexOf(int x, int y) const;

};

