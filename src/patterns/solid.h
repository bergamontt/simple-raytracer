#pragma once
#include "../const_colors.h"
#include "pattern.h"

class Solid : public Pattern
{

public:

	Solid(const Color& color)
		: _color{ color }
	{}

	Solid()
		: _color{ WHITE }
	{}

	const Color colorAt(const Tuple& point) const override;
	const Color& baseColor() const;

private:

	Color _color;

};