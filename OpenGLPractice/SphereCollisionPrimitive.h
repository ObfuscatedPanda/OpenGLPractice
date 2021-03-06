#pragma once
#include "collisionprimitive.h"
class SphereCollisionPrimitive :
	public CollisionPrimitive
{
public:
	SphereCollisionPrimitive(void);
	~SphereCollisionPrimitive(void);
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


/* SPHERE EQUATIONS
Cartesian Coordinate System
(x - xo)^2 + (y - yo)^2 + (z - zo)^2 = r^2

Spherical Coordinate System
r <= ro

Spherical


*/

};

