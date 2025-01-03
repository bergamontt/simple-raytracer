#pragma once
#include "../material.h"
#include "../matrix.h"
#include "../constants.h"

class Sphere
{
public:
	
	Sphere()
		: _thisID{ ++_ID }
	{}

	Sphere(const Sphere& s)
		: _radius{s._radius}
		, _material{s._material}
		, _origin{s._origin}
		, _transform{s._transform}
		, _thisID{ s._ID }
	{}

	const Tuple normalAt(const Tuple& point) const;

	const Matrix transform() const;
	const Material material() const;
	const Tuple origin() const;
	const float radius() const;
	const int id() const;

	void setTransform(const Matrix& m);
	void setMaterial(const Material& m);

private:

	float _radius = 1.0f;
	Material _material;
	Tuple _origin = createPoint(0.0f, 0.0f, 0.0f);
	Matrix _transform = Matrix::indentityMatrix(TRANSFORM_N);
	
	int _thisID;
	inline static int _ID;

};

bool operator==(const Sphere& a, const Sphere& b);