#pragma once

#include "constants.h"

using namespace std;

template<typename T, typename U>
inline bool equalDouble(const T& a, const U& b) {
	return (fabs(a - b) < EPSILON);
}