#pragma once
#include "shapes/shape.h"

inline const Color lightning(const Material& m,
	const ShapeConstPtr& shape, const Light& light, const Tuple& position, const Tuple& eyev,
	const Tuple& normalv, bool inShadow)
{
	Color materialColor = m.color;
	if (shape != nullptr && hasPattern(m))
		materialColor = shape->patternColorAt(position);
	else if (hasPattern(m))
		materialColor = m.pattern->colorAt(position);

	Color effectiveColor = materialColor * light.intensity();
	Tuple lightv = normalize(light.position() - position);
	Color ambidient = effectiveColor * m.ambient;

	if (inShadow)
		return ambidient;

	Color diffuse = BLACK;
	Color specular = BLACK;
	float lightDotNormal = dot(lightv, normalv);
	if (lightDotNormal >= 0.0)
	{
		diffuse = effectiveColor * m.diffuse * lightDotNormal;

		Tuple reflectv = reflect(-lightv, normalv);
		float reflectDotEye = dot(reflectv, eyev);
		if (reflectDotEye > 0.0)
		{
			float factor = pow(reflectDotEye, m.shininess);
			specular = light.intensity() * m.specular * factor;
		}
	}

	return ambidient + diffuse + specular;
}