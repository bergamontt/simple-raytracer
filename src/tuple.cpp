#include "tuple.h"
#include <cmath>

Tuple createTuple(const float x, const float y, const float z, const float w)
{
	return { x, y, z, w };
}

Tuple createPoint(const float x, const float y, const float z)
{
	return { x, y, z, POINT };
}

Tuple createVector(const float x, const float y, const float z)
{
	return { x, y, z, VECTOR };
}

const Tuple operator*(const Tuple& a, const float b)
{
	return { a._x * b, a._y * b, a._z * b, a._w * b };
}

const Tuple operator+(const Tuple& a, const Tuple& b)
{
	return { a._x + b._x, a._y + b._y, a._z + b._z, a._w + b._w };
}

const Tuple operator-(const Tuple& a, const Tuple& b)
{
	return { a._x - b._x, a._y - b._y, a._z - b._z, a._w - b._w };
}

const Tuple operator-(const Tuple& a)
{
	return { createVector(0.0, 0.0, 0.0) - a };
}


bool operator==(const Tuple& a, const Tuple& b)
{
	return equalDouble(a._x, b._x) && equalDouble(a._y, b._y)
		&& equalDouble(a._z, b._z) && equalDouble(a._w, b._w);
}

float magnitude(const Tuple& a)
{
	return std::sqrt(a._x * a._x + a._y * a._y + a._z * a._z + a._w * a._w);
}

const Tuple reflect(const Tuple& inVector, const Tuple& normal)
{
	return inVector - normal * 2 * dot(inVector, normal);
}

const Tuple normalize(const Tuple& a)
{
	float m = magnitude(a);
	return { a._x / m, a._y / m, a._z / m, a._w / m };
}

float dot(const Tuple& a, const Tuple& b)
{
	return { a._x * b._x + a._y * b._y + a._z * b._z + a._w * b._w };
}

const Tuple cross(const Tuple& a, const Tuple& b)
{
	return createVector(a._y * b._z - a._z * b._y,
		a._z * b._x - a._x * b._z,
		a._x * b._y - a._y * b._x);
}

bool isPoint(const Tuple& tuple)
{
	return tuple._w == POINT;
}

bool isVector(const Tuple& tuple)
{
	return tuple._w == VECTOR;
}