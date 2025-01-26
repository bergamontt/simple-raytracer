#pragma once
#include "shape.h"
#include <vector>

class Group : public Shape
{

public:

	optional<Intersections> localIntersection(const Ray& ray) const override;
	void setTransform(const Matrix& m) override;

	void addChild(ShapePtr& child);
	
	const ShapePtr& getChild(int index) const;

	int size() const;

protected:

	const Tuple localNormal(const Tuple& point) const override;

private:

	vector<ShapePtr> _group;

};