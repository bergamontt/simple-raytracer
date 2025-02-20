#pragma once
#include "pattern.h"
#include "solid.h"
#include "../const_colors.h"

class Stripe : public Pattern
{
public:

	Stripe(const Pattern* const fst,
		   const Pattern* const scd)
		: _fst{ fst }
		, _scd{ scd }
	{}

	const Color colorAt(const Tuple& point) const override;

private:

	const Pattern* _fst;
	const Pattern* _scd;

};
