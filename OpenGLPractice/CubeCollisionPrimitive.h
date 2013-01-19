#pragma once
#include "collisionprimitive.h"
class CubeCollisionPrimitive :
	public CollisionPrimitive
{
public:
	CubeCollisionPrimitive(void);
	~CubeCollisionPrimitive(void);
	bool Intersects(CollisionPrimitive* otherCollisionPrimitive);
};

