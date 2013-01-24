#pragma once
#include "CollisionPrimitive.h"
class OBBCollisionPrimitive :
	public CollisionPrimitive
{
public:
	OBBCollisionPrimitive(void);
	~OBBCollisionPrimitive(void);
	bool IntersectPoint(PointCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectLine(LineCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectOBB(OBBCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectAABB(AABBCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectCylinder(CylinderCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectSphere(SphereCollisionPrimitive* otherCollisionPrimitive);
};

