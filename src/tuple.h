#pragma once

#include "constants.h"
#include "func.h"

using namespace std;

struct Tuple {
	float x, y, z, w;
};

inline Tuple createTuple(const float x, const float y, const float z, const float w) {
	return { x, y, z, w };
}

inline Tuple createPoint(const float x, const float y, const float z) {
	return { x, y, z, POINT };
}

inline Tuple createVector(const float x, const float y, const float z) {
	return { x, y, z, VECTOR };
}

inline const Tuple operator+(const Tuple& a, const Tuple& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

inline const Tuple operator-(const Tuple& a, const Tuple& b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

inline const Tuple operator-(const Tuple& a) {
	return { createVector(0.0, 0.0, 0.0) - a};
}

template<typename T>
inline const Tuple operator*(const Tuple& a, const T& b) {
	return { a.x * b, a.y * b, a.z * b, a.w * b };
}

inline bool operator==(const Tuple& a, const Tuple& b) {
	return equalDouble(a.x, b.x) && equalDouble(a.y, b.y)
		&& equalDouble(a.z, b.z) && equalDouble(a.w, b.w);
}

inline float magnitude(const Tuple& a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

inline const Tuple normalize(const Tuple& a) {
	float m = magnitude(a);
	return { a.x / m, a.y / m, a.z / m, a.w / m };
}

inline float dot(const Tuple& a, const Tuple& b) {
	return { a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w };
}

inline const Tuple cross(const Tuple& a, const Tuple& b) {
	return createVector(a.y * b.z - a.z * b.y, 
						a.z * b.x - a.x * b.z,
						a.x * b.y - a.y * b.x);
}

inline bool isPoint(const Tuple& tuple) {
	return tuple.w == POINT;
}

inline bool isVector(const Tuple& tuple) {
	return tuple.w == VECTOR;
}