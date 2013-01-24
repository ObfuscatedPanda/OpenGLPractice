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
	Vector myPosition = this->position;
	SCALAR myRadius = this->radius;
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


		


bool SphereCollisionPrimitive::IntersectPoint(PointCollisionPrimitive* otherCollisionPrimitive)
{
	PointCollisionPrimitive* otherPoint = (PointCollisionPrimitive*) otherCollisionPrimitive;
	Vector pointPosition = otherPoint->Position();
	Vector positionDifference(this->position - pointPosition);
	return radius * radius > (positionDifference.LengthSquared());
}

bool SphereCollisionPrimitive::IntersectCube(CubeCollisionPrimitive* otherCollisionPrimitive)
{
	// To keep things simple, we will first transform to be axis aligned

	// We have a few options here:
	/*   1. If a line can be constructed which is perpendicular to the face of the cube in question
	        and an imaginary face passing through the center of the sphere and parallel to the cube face,
			test the end-point at the non-sphere-center end of the line - check if it is on the other side
			of the face/plane - if it is, we have a hit
			If one can't be constructed, check each vertex
		 2. Find the closest point on the cube face to the center of the sphere, if it is a distance greater
		    than the sphere's radius away, we have no collision
	     3. Transform the sphere to cartesian or the cube to polar coordinate systems and see if one satisfies 
		    the others' equations - the sphere -> cartesion transformation will probably be much simpler
			for our case, particularly because we deal primarily in cartesian coordinates.
	*/

	assert(1); /// Not Implemented
}

bool SphereCollisionPrimitive::IntersectCylinder(CylinderCollisionPrimitive* otherCollisionPrimitive)
{
	// Transform to be axis aligned - simplify this later

	// Transform this into a cylinder-cylinder collision

	assert(1); /// Not Implemented
}

bool SphereCollisionPrimitive::IntersectSphere(SphereCollisionPrimitive* otherCollisionPrimitive)
{   
	SphereCollisionPrimitive* otherSphere = (SphereCollisionPrimitive*) otherCollisionPrimitive;
	Vector otherSpherePosition = otherSphere->Position();
	SCALAR radiusSum = otherSphere->Radius() + radius;
	Vector positionDifference(this->Position() - otherSpherePosition);
	return radiusSum * radiusSum >= positionDifference.LengthSquared();
}