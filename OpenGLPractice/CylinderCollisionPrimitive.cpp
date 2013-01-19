#include "CylinderCollisionPrimitive.h"


CylinderCollisionPrimitive::CylinderCollisionPrimitive(void)
{
}


CylinderCollisionPrimitive::~CylinderCollisionPrimitive(void)
{
}

bool CylinderCollisionPrimitive::Intersects(CollisionPrimitive* otherCollisionPrimitive)
{
	assert(E_CPT_CYLINDER == otherCollisionPrimitive->PrimitiveType());

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

bool CylinderCollisionPrimitive::IntersectPoint(PointCollisionPrimitive* otherCollisionPrimitive)
{
	assert(1); /// Not Implemented
}

bool CylinderCollisionPrimitive::IntersectCube(CubeCollisionPrimitive* otherCollisionPrimitive)
{
	assert(1); /// Not Implemented
}

bool CylinderCollisionPrimitive::IntersectCylinder(CylinderCollisionPrimitive* otherCollisionPrimitive)
{
	assert(1); /// Not Implemented
}

bool CylinderCollisionPrimitive::IntersectSphere(SphereCollisionPrimitive* otherCollisionPrimitive)
{
	assert(1); /// Not Implemented
}