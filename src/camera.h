#pragma once
#include "constants.h"
#include "canvas.h"
#include "matrix.h"
#include "ray.h"
#include "world.h"

class Camera
{

public:

	Camera(int hsize, int vsize, float fieldOfView)
		: _hsize{ hsize }
		, _vsize{ vsize }
		, _fieldOfView{ fieldOfView }
		, _transform{Matrix::indentityMatrix(TRANSFORM_N)}
	{
		calculateHalfAndPixelSize();
	}

	const Canvas render(const World& w);
	const Ray rayForPixel(int x, int y) const;

	int hsize() const;
	int vsize() const;
	float fieldOfView() const;
	float pixelSize() const;

	void setTransform(const Matrix& m);

private:

	int _hsize;
	int _vsize;

	float _fieldOfView;

	Matrix _transform;

	float _halfWidth;
	float _halfHeight;
	float _pixelSize;

	void calculateHalfSize();
	void calculatePixelSize();
	void calculateHalfAndPixelSize();

};