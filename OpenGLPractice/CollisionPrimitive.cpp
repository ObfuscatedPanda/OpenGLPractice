#include "CollisionPrimitive.h"


CollisionPrimitive::CollisionPrimitive(void)
{
}


CollisionPrimitive::~CollisionPrimitive(void)
{
}

bool CollisionPrimitive::Intersects(CollisionPrimitive* otherCollisionPrimitive)
{
	switch(primitiveType)
	{
	E_CPT_POINT:
		((PointCollisionPrimitive*)this)->Intersects(otherCollisionPrimitive);		
		assert(1); // Not Implemented
		break;

	E_CPT_LINE:
		((LineCollisionPrimitive*)this)->Intersects(otherCollisionPrimitive);		
		assert(1); // Not Implemented
		break;

	E_CPT_OBB:
		((OBBCollisionPrimitive*)this)->Intersects(otherCollisionPrimitive);
		assert(1); // Not Implemented
		break;
		
	E_CPT_AABB:
		((AABBCollisionPrimitive*)this)->Intersects(otherCollisionPrimitive);
		assert(1); // Not Implemented
		break;
	
	E_CPT_SPHERE:
		((SphereCollisionPrimitive*)this)->Intersects(otherCollisionPrimitive);
		assert(1); // Not Implemented
		break;
	
	E_CPT_CYLINDER:
		((CylinderCollisionPrimitive*)this)->Intersects(otherCollisionPrimitive);
		assert(1); // Not Implemented
		break;
	
	E_CPT_CAPSULE:
		assert(1); // Not Implemented
		break;
	
	E_CPT_CONE:
		assert(1); // Not Implemented
		break;
	
	E_CPT_NULL:
		assert(1); // Not Implemented
		break;

	default:
		assert(1); /// InvalidCollisionPrimitiveTypeDefined
		break;

	}
}