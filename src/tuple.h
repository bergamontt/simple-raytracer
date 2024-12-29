#pragma once

#include "constants.h"
#include "func.h"

struct Tuple
{
	float _x, _y, _z, _w;
};

Tuple createTuple(const float x, const float y, const float z, const float w);
Tuple createPoint(const float x, const float y, const float z);
Tuple createVector(const float x, const float y, const float z);

const Tuple operator*(const Tuple& a, const float b);
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