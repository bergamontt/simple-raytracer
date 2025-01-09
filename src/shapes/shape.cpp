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

const Matrix& Shape::transform() const
{
	return _transform;
}

const Material& Shape::material() const
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
