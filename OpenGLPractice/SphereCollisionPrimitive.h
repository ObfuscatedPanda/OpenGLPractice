#pragma once
#include "collisionprimitive.h"
class SphereCollisionPrimitive :
	public CollisionPrimitive
{
public:
	SphereCollisionPrimitive(void);
	~SphereCollisionPrimitive(void);
	bool Intersects(CollisionPrimitive* otherCollisionPrimitive);
	inline Vector3d Position(void) { return position; }
	inline float Radius(void) { return radius; }

private:
	Vector3d position;
	float radius;
};

