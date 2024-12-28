#include "transformation.h"
#include "matrix.h"
#include "constants.h"
#include <cmath>

const Matrix translation(float x, float y, float z)
{
	Matrix translation = Matrix::indentityMatrix(TRANSFORM_N);
	translation.set(0, 3, x);
	translation.set(1, 3, y);
	translation.set(2, 3, z);
	return translation;
}

const Matrix scaling(float x, float y, float z)
{
	Matrix scaling = Matrix::indentityMatrix(TRANSFORM_N);
	scaling.set(0, 0, x);
	scaling.set(1, 1, y);
	scaling.set(2, 2, z);
	return scaling;
}

const Matrix rotationX(float degree)
{
	Matrix rotation = Matrix::indentityMatrix(TRANSFORM_N);
	float cosd = cos(degree);
	float sind = sin(degree);
	rotation.set(1, 1,  cosd);
	rotation.set(1, 2, -sind);
	rotation.set(2, 1,  sind);
	rotation.set(2, 2,  cosd);
	return rotation;
}

const Matrix rotationY(float degree)
{
	Matrix rotation = Matrix::indentityMatrix(TRANSFORM_N);
	float cosd = cos(degree);
	float sind = sin(degree);
	rotation.set(0, 0,  cosd);
	rotation.set(0, 2,  sind);
	rotation.set(2, 0, -sind);
	rotation.set(2, 2,  cosd);
	return rotation;
}

const Matrix rotationZ(float degree)
{
	Matrix rotation = Matrix::indentityMatrix(TRANSFORM_N);
	float cosd = cos(degree);
	float sind = sin(degree);
	rotation.set(0, 0,  cosd);
	rotation.set(0, 1, -sind);
	rotation.set(1, 0,  sind);
	rotation.set(1, 1,  cosd);
	return rotation;
}

const Matrix skew(float xy, float xz, float yx, float yz, float zx, float zy)
{
	Matrix rotation = Matrix::indentityMatrix(TRANSFORM_N);
	rotation.set(0, 1, xy);
	rotation.set(0, 2, xz);
	rotation.set(1, 0, yx);
	rotation.set(1, 2, yz);
	rotation.set(2, 0, zx);
	rotation.set(2, 1, zy);
	return rotation;
}