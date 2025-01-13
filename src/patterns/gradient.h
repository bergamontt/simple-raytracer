#pragma once
#include "../const_colors.h"
#include "pattern.h"


class Gradient : public Pattern
{

public:

	Gradient(const Pattern* const fst,
		const Pattern* const scd)
		: _fst{ fst }
		, _scd{ scd }
	{}

	const Color colorAt(const Tuple& point) const override;

private:

	const Pattern* _fst;
	const Pattern* _scd;

};