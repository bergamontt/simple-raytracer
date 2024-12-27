#pragma once

#include "constants.h"
#include "func.h"

struct Tuple
{
	float x, y, z, w;
};

Tuple createTuple(const float x, const float y, const float z, const float w);
Tuple createPoint(const float x, const float y, const float z);
Tuple createVector(const float x, const float y, const float z);

template<typename T>
inline const Tuple operator*(const Tuple& a, const T& b)
{
	return { a.x * b, a.y * b, a.z * b, a.w * b };
}

const Tuple operator+(const Tuple& a, const Tuple& b);
const Tuple operator-(const Tuple& a, const Tuple& b);
const Tuple operator-(const Tuple& a);

bool operator==(const Tuple& a, const Tuple& b);

float magnitude(const Tuple& a);
const Tuple normalize(const Tuple& a);
float dot(const Tuple& a, const Tuple& b);
const Tuple cross(const Tuple& a, const Tuple& b);

bool isPoint(const Tuple& tuple);
bool isVector(const Tuple& tuple);