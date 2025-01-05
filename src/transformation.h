#pragma once
#include "tuple.h"

class Matrix;

const Matrix translation(float x, float y, float z);
const Matrix scaling(float x, float y, float z);

const Matrix rotationX(float degree);
const Matrix rotationY(float degree);
const Matrix rotationZ(float degree);

const Matrix skew(float xy, float xz,
				  float yx, float yz,
				  float zx, float zy);

const Matrix viewTransform(const Tuple& from,
						   const Tuple& to,
						   const Tuple& upVector);