#pragma once

#include "func.h"

struct Color {
	float red, green, blue;
};

inline const Color createColor(const float red, const float green, const float blue) {
	return { red, green, blue };
}

inline const Color operator+(const Color& a, const Color& b) {
	return { a.red + b.red, a.green + b.green, a.blue + b.blue };
}

inline const Color operator-(const Color& a, const Color& b) {
	return { a.red - b.red, a.green - b.green, a.blue - b.blue };
}

inline const Color operator*(const Color& a, const Color& b) {
	return { a.red * b.red, a.green * b.green, a.blue * b.blue };
}

template<typename T>
inline const Color operator*(const Color& a, const T& b) {
	return { a.red * b, a.green * b, a.blue * b };
}

inline bool operator==(const Color& a, const Color& b) {
	return equalDouble(a.red, b.red) && equalDouble(a.green, b.green)
		&& equalDouble(a.blue, b.blue);
}