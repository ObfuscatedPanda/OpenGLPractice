#include "SphereCollisionPrimitive.h"


SphereCollisionPrimitive::SphereCollisionPrimitive(void)
{
}


SphereCollisionPrimitive::~SphereCollisionPrimitive(void)
{
}

bool SphereCollisionPrimitive::Intersects(CollisionPrimitive* otherCollisionPrimitive)
{
	assert(E_CPT_SPHERE == otherCollisionPrimitive->PrimitiveType());
	Vector3d myPosition = this->position;
	float myRadius = this->radius;
	bool primitivesIntersect = false;

	switch(otherCollisionPrimitive->PrimitiveType())
	{
	E_CPT_POINT:
		IntersectsPoint((PointCollisionPrimitive*) otherCollisionPrimitive);
		break;

	E_CPT_CUBE:
		
		break;
	
	E_CPT_SPHERE: // Need to fix
		IntersectsSphere((SphereCollisionPrimitive*) otherCollisionPrimitive);	
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


IntersectsPoint((PointCollisionPrimitive*) otherCollisionPrimitive);
		PointCollisionPrimitive* otherPoint = (PointCollisionPrimitive*) otherCollisionPrimitive;
		Vector3d pointPosition = otherPoint->Position();
		Vector3d positionDifference(this->position.X() - pointPosition.X(),
									this->position.Y() - pointPosition.Y(),
									this->position.Z() - pointPosition.Z());
		return radius > (	positionDifference.X() * positionDifference.X() +
							positionDifference.Y() * positionDifference.Y() +
							positionDifference.Z() * positionDifference.Z());



		IntersectsSphere((SphereCollisionPrimitive*) otherCollisionPrimitive);	
		SphereCollisionPrimitive* otherSphere = (SphereCollisionPrimitive*) otherCollisionPrimitive;
		Vector3d otherSpherePosition = otherSphere->Position();
		Vector3d positionDifference(this->position.X() - otherSpherePosition.X(),
									this->position.Y() - otherSpherePosition.Y(),
									this->position.Z() - otherSpherePosition.Z());
		return (this.x - radius) ^ 2 + ... > (	positionDifference.X() * positionDifference.X() +
							positionDifference.Y() * positionDifference.Y() +
							positionDifference.Z() * positionDifference.Z());