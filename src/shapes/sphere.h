#pragma once
#include "../tuple.h"
#include "../matrix.h"
#include "../constants.h"

class Sphere
{
public:
	
	Sphere()
		: _thisID{ ++_ID }
	{}

	Sphere(const Sphere& s)
		: _thisID{ s._ID }
	{}

	const Matrix transform() const;
	void setTransform(const Matrix& m);

	const Tuple origin() const;
	const float radius() const;
	const int id() const;

private:
	
	Matrix _transform = Matrix::indentityMatrix(TRANSFORM_N);
	Tuple _origin = createPoint(0.0f, 0.0f, 0.0f);
	float _radius = 1;
	
	int _thisID;
	inline static int _ID;

};

bool operator==(const Sphere& a, const Sphere& b);