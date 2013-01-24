#pragma once
#include "Collisionprimitive.h"
#include "Vector.h"

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
	Vector p1;
	Vector p2;
};

