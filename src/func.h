#pragma once

#include "constants.h"

template<typename T>
inline float fabs(const T& a)
{
	return a < 0 ? -a : a;
}

template<typename T, typename U>
inline bool equalDouble(const T& a, const U& b)
{
	return (fabs(a - b) < EPSILON);
}