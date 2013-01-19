#include "PointCollisionPrimitive.h"


PointCollisionPrimitive::PointCollisionPrimitive(void)
{
}


PointCollisionPrimitive::~PointCollisionPrimitive(void)
{
}


bool PointCollisionPrimitive::Intersects(CollisionPrimitive* otherCollisionPrimitive)
{
	assert(E_CPT_POINT == otherCollisionPrimitive->PrimitiveType());

	switch(otherCollisionPrimitive->PrimitiveType())
	{
	E_CPT_POINT:
		((PointCollisionPrimitive*)this)->Intersects(otherCollisionPrimitive);		
		assert(1); // Not Implemented
		break;

	E_CPT_CUBE:
		((CubeCollisionPrimitive*)this)->Intersects(otherCollisionPrimitive);
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