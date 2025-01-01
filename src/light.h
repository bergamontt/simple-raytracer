#pragma once
#include "tuple.h"
#include "color.h"

class Light
{

public:

	Light(const Tuple& position, const Color& intensity)
		: _position{ position }
		, _intensity{ intensity }
	{}

	const Tuple position() const;
	const Color intensity() const;

private:

	Tuple _position;
	Color _intensity;

};