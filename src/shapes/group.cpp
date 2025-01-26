#include "group.h"

void Group::addChild(ShapePtr& child)
{
	child->setParent(shared_from_this());
	_group.emplace_back(child);
}

const ShapePtr& Group::getChild(int index) const
{
	return _group.at(index);
}

int Group::size() const
{
	return _group.size();
}

optional<Intersections> Group::localIntersection(const Ray& ray) const
{
	Intersections groupIntrs;
	for (int i = 0; i < size(); ++i)
	{
		const ShapePtr& child = getChild(i);
		optional<Intersections> childPosIntrs = ray.intersect(child);
		if (!childPosIntrs.has_value())
			continue;
		Intersections& childIntrs = childPosIntrs.value();
		groupIntrs.merge(childIntrs);
	}
	return groupIntrs;
}

void Group::setTransform(const Matrix& transform)
{
	for (int i = 0; i < size(); ++i)
	{
		const ShapePtr& child = getChild(i);
		child->setTransform(transform);
	}
	_transform = transform;
}

const Tuple Group::localNormal(const Tuple& point) const
{
	return {};
}
