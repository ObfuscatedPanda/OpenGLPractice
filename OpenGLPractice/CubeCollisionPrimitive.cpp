#include "CubeCollisionPrimitive.h"


CubeCollisionPrimitive::CubeCollisionPrimitive(void)
{
}


CubeCollisionPrimitive::~CubeCollisionPrimitive(void)
{
}

bool CubeCollisionPrimitive::Intersects(CollisionPrimitive* otherCollisionPrimitive)
{
	assert(E_CPT_CUBE == otherCollisionPrimitive->PrimitiveType());

	switch(otherCollisionPrimitive->PrimitiveType())
	{
	E_CPT_POINT:
		
		break;

	E_CPT_CUBE:
		
		break;
	
	E_CPT_SPHERE:
		
		break;
	
	E_CPT_CYLINDER:
		
		break;
	
	E_CPT_CAPSULE:
		
		break;
	
	E_CPT_CONE:
		
		break;
	
	E_CPT_NULL:
		
		break;

	default:
		assert(1); /// InvalidCollisionPrimitiveTypeDefined
		break;

	}
}