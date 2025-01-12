#pragma once
#include "pattern.h"
#include "../const_colors.h"

class Stripe : public Pattern
{
public:

	Stripe(const Color& fst, const Color& scd)
		: _fst{ fst }
		, _scd{ scd }
	{}

	Stripe()
		: _fst{ WHITE }
		, _scd{ BLACK }
	{}
	
	const Color colorAt(const Tuple& point) const override;

	const Color& firstColor() const;
	const Color& secondColor() const;

private:

	Color _fst;
	Color _scd;

};
