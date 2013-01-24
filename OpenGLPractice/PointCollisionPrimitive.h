#pragma once
#include "collisionprimitive.h"
class PointCollisionPrimitive :
	public CollisionPrimitive
{
public:
	PointCollisionPrimitive(void);
	~PointCollisionPrimitive(void);
	bool Intersects(CollisionPrimitive* otherCollisionPrimitive);
	inline Vector Position(void) { return position; }
	inline SCALAR Radius(void) { return radius; }

private:
	bool IntersectPoint(PointCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectCube(CubeCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectCylinder(CylinderCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectSphere(SphereCollisionPrimitive* otherCollisionPrimitive);
	Vector position;
	SCALAR radius;
};

