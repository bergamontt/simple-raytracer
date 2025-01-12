#pragma once
#include "../color.h"
#include "../tuple.h"
#include "../matrix.h"

class Pattern
{

public:

	const Matrix& transform() const;
	void setTransform(const Matrix& m);

	virtual const Color colorAt(const Tuple& point) const = 0;

private:

	Matrix _transform;

};