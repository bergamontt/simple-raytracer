#pragma once
#include "../tuple.h"

class Sphere
{
public:
	
	Sphere()
		: _thisID{ ++_ID }
	{}

	const Tuple origin() const;
	const float radius() const;
	const int id() const;

private:
	
	Tuple _origin = createPoint(0.0f, 0.0f, 0.0f);
	float _radius = 1;
	
	const int _thisID;
	inline static int _ID;

};

bool operator==(const Sphere& a, const Sphere& b);