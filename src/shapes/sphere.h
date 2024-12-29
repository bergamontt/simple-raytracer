#pragma once
#include "../tuple.h"

class Sphere
{
public:
	
	Sphere() = default;

private:
	
	Tuple _origin = createPoint(0.0f, 0.0f, 0.0f);
	int _radius = 1;

};

