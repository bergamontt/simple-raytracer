#pragma once
#include "light.h"
#include "const_colors.h"
#include "func.h"

struct Material
{
	Color color = WHITE;
	float ambient = 0.1f;
	float diffuse = 0.9f;
	float specular = 0.9f;
	float shininess = 200.0f;
};

inline const Color lightning(const Material& m, const Light& light,
	const Tuple& position, const Tuple& eyev, const Tuple& normalv,
	bool inShadow)
{
	Color effectiveColor = m.color * light.intensity();
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

inline bool operator==(const Material& a, const Material& b)
{
	return equalDouble(a.ambient, b.ambient) && equalDouble(a.diffuse, b.diffuse)
		&& equalDouble(a.shininess, b.shininess) && equalDouble(a.specular, b.specular)
		&& a.color == b.color;
}