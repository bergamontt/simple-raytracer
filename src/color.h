#pragma once

#include "constants.h"
#include <ostream>
#include "func.h"

struct Color
{
	float _red, _green, _blue;
};

inline const Color pixelToPPM(const Color& a)
{
	return { a._red   * MAX_COLOR_VALUE,
			 a._green * MAX_COLOR_VALUE ,
			 a._blue  * MAX_COLOR_VALUE  };
}

inline const Color createColor(const float red, const float green, const float blue)
{
	return { red, green, blue };
}

inline std::ostream& operator<<(std::ostream& os, const Color& a)
{
	os << a._red << ' ' << a._green << ' ' << a._blue;
	return os;
}

inline const Color operator+(const Color& a, const Color& b)
{
	return { a._red + b._red, a._green + b._green, a._blue + b._blue };
}

inline const Color operator-(const Color& a, const Color& b)
{
	return { a._red - b._red, a._green - b._green, a._blue - b._blue };
}

inline const Color operator*(const Color& a, const Color& b)
{
	return { a._red * b._red, a._green * b._green, a._blue * b._blue };
}

template<typename T>
inline const Color operator*(const Color& a, const T& b)
{
	return { a._red * b, a._green * b, a._blue * b };
}

inline bool operator==(const Color& a, const Color& b)
{
	return equalDouble(a._red, b._red) && equalDouble(a._green, b._green)
		&& equalDouble(a._blue, b._blue);
}