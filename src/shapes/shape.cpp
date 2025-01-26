#include "shape.h"

const Tuple Shape::normalToWorld(const Tuple& vector) const
{ 
	Tuple worldVector = transform().inverse().transpose() * vector;
	worldVector._w = 0;
	worldVector = normalize(worldVector);
	if (hasParent())
		worldVector = parent()->normalToWorld(worldVector);
	return worldVector;
}

const Tuple Shape::worldToObject(const Tuple& point) const
{
	Tuple objPoint(point);
	if (hasParent())
		objPoint = parent()->worldToObject(point);
	return transform().inverse() * objPoint;
}

const Tuple Shape::normalAt(const Tuple& point) const
{
	Tuple localPoint = worldToObject(point);
	Tuple localVector = localNormal(localPoint);
	return normalToWorld(localVector);
}

const Color Shape::patternColorAt(const Tuple& worldPoint) const
{
	Tuple objectPoint = _transform.inverse() * worldPoint;
	Pattern* materialPattern = _material.pattern;
	const Matrix& patternTransform = materialPattern->transform();
	Tuple patternPoint = patternTransform.inverse() * objectPoint;
	return materialPattern->colorAt(patternPoint);
}

bool Shape::hasParent() const
{
	return parent() != nullptr;
}

const ShapePtr& Shape::parent() const
{
	return _parent;
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

void Shape::setParent(const ShapePtr& parent)
{
	_parent = parent;
}