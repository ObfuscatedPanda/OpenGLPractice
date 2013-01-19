#pragma once
#include "collisionprimitive.h"
class CylinderCollisionPrimitive :
	public CollisionPrimitive
{
public:
	CylinderCollisionPrimitive(void);
	~CylinderCollisionPrimitive(void);
	bool Intersects(CollisionPrimitive* otherCollisionPrimitive);

private:
	bool IntersectPoint(PointCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectCube(CubeCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectCylinder(CylinderCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectSphere(SphereCollisionPrimitive* otherCollisionPrimitive);
};

