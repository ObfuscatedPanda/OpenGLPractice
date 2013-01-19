#pragma once
#include "Collisionprimitive.h"
#include "Vector3d.h"

class LineCollisionPrimitive :
	public CollisionPrimitive
{
public:
	LineCollisionPrimitive(void);
	~LineCollisionPrimitive(void);
	bool Intersects(CollisionPrimitive* otherCollisionPrimitive);

private:
	bool IntersectPoint(PointCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectCube(CubeCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectCylinder(CylinderCollisionPrimitive* otherCollisionPrimitive);
	bool IntersectSphere(SphereCollisionPrimitive* otherCollisionPrimitive);
	Vector3d p1;
	Vector3d p2;
};

