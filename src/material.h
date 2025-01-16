#pragma once
#include "light.h"
#include "const_colors.h"
#include "func.h"
#include "patterns/pattern.h"

struct Material
{
	Color color = WHITE;
	float ambient = 0.1f;
	float diffuse = 0.9f;
	float specular = 0.9f;
	float shininess = 200.0f;
	Pattern* pattern = nullptr;
	float reflective = 0.0f;
	float transparency = 0.0f;
	float reflactiveIndex = 1.0f;
};

inline bool hasPattern(const Material& m)
{
	return m.pattern != nullptr;
}

inline bool operator==(const Material& a, const Material& b)
{
	return equalDouble(a.ambient, b.ambient) && equalDouble(a.diffuse, b.diffuse)
		&& equalDouble(a.shininess, b.shininess) && equalDouble(a.specular, b.specular)
		&& a.color == b.color;
}