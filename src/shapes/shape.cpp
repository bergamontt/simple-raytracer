#include "shape.h"

const Tuple Shape::normalAt(const Tuple& point) const
{
	Matrix transformInverse = _transform.inverse();
	Tuple objectPoint = transformInverse * point;
	Tuple objectNormal = localNormal(objectPoint);
	Tuple worldNormal = transformInverse.transpose() * objectNormal;
	worldNormal._w = 0;
	return normalize(worldNormal);
}

const Color Shape::patternColorAt(const Tuple& worldPoint) const
{
	Tuple objectPoint = _transform.inverse() * worldPoint;
	Pattern* materialPattern = _material.pattern;
	const Matrix& patternTransform = materialPattern->transform();
	Tuple patternPoint = patternTransform.inverse() * objectPoint;
	return materialPattern->colorAt(patternPoint);
}

const Matrix& Shape::transform() const
{
	return _transform;
}

const Material& Shape::material() const
{
	return _material;
}

Material& Shape::material()
{
	return _material;
}

void Shape::setTransform(const Matrix& transform)
{
	_transform = transform;
}

void Shape::setMaterial(const Material& material)
{
	_material = material;
}
