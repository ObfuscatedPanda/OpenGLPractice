#pragma once
#include "Collidable.h"
#include "PointCollisionPrimitive.h"
#include "CubeCollisionPrimitive.h"
#include "SphereCollisionPrimitive.h"
#include "CylinderCollisionPrimitive.h"
#include "Vector.h"

enum collisionPrimitiveType
{
	E_CPT_POINT,
	E_CPT_OBB,
	E_CPT_AABB,
	E_CPT_SPHERE,
	E_CPT_CYLINDER,
	E_CPT_CAPSULE,
	E_CPT_CONE,
	E_CPT_LINE,
	E_CPT_NULL
};


class CollisionPrimitive :
	public Collidable
{
public:
	CollisionPrimitive(void);
	~CollisionPrimitive(void);
	virtual bool Intersects(CollisionPrimitive* otherCollisionPrimitive);
	inline collisionPrimitiveType PrimitiveType(void) { return primitiveType; }

private:
	collisionPrimitiveType primitiveType;
};

