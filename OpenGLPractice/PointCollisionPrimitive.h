#pragma once
#include "collisionprimitive.h"
class PointCollisionPrimitive :
	public CollisionPrimitive
{
public:
	PointCollisionPrimitive(void);
	~PointCollisionPrimitive(void);
	bool Intersects(CollisionPrimitive* otherCollisionPrimitive);
	inline Vector3d Position(void) { return position; }
	inline float Radius(void) { return radius; }

private:
	Vector3d position;
	float radius;
};

