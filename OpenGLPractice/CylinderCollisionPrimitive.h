#pragma once
#include "collisionprimitive.h"
class CylinderCollisionPrimitive :
	public CollisionPrimitive
{
public:
	CylinderCollisionPrimitive(void);
	~CylinderCollisionPrimitive(void);
	bool Intersects(CollisionPrimitive* otherCollisionPrimitive);
};

