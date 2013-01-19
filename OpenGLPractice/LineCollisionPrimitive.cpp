#include "LineCollisionPrimitive.h"


LineCollisionPrimitive::LineCollisionPrimitive(void)
{
}


LineCollisionPrimitive::~LineCollisionPrimitive(void)
{
}

bool LineCollisionPrimitive::Intersects(CollisionPrimitive* otherCollisionPrimitive)
{
	assert(E_CPT_LINE == otherCollisionPrimitive->PrimitiveType());

	switch(otherCollisionPrimitive->PrimitiveType())
	{
	E_CPT_POINT:
		IntersectPoint((PointCollisionPrimitive*)otherCollisionPrimitive);
		
		break;

	E_CPT_CUBE:
		IntersectCube((CubeCollisionPrimitive*)otherCollisionPrimitive);
		
		break;
	
	E_CPT_SPHERE:
		IntersectSphere((SphereCollisionPrimitive*)otherCollisionPrimitive);
		
		break;
	
	E_CPT_CYLINDER:
		IntersectCylinder((CylinderCollisionPrimitive*)otherCollisionPrimitive);
		break;
	
	E_CPT_CAPSULE:
		assert(1); /// Not Implemented
		break;
	
	E_CPT_CONE:
		assert(1); /// Not Implemented
		break;
	
	E_CPT_NULL:
		assert(1); /// Not Implemented
		break;

	default:
		assert(1); /// InvalidCollisionPrimitiveTypeDefined
		break;

	}
}


bool LineCollisionPrimitive::IntersectPoint(PointCollisionPrimitive* otherCollisionPrimitive)
{
	/* Using line equations
		x = xo + a * t
		y = yo + b * t
		z = zo + c * t

	and (x - xo)/a = (y - yo)/b = (z - zo)/c
	*/
	float a = 0, b = 0, c = 0;	
	float t = 0;		// This is the squared value of the actual length
	float componentDifference [3] =  {p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z()};
	for(int i = 0; i < 3; i++)
	{
		t += (componentDifference[i] * componentDifference[i]);
	}
	// The values of a, b, and c will be transformed in a non linear way... must investigate farther

	
	assert(1); /// Not Implemented
}

bool LineCollisionPrimitive::IntersectCube(CubeCollisionPrimitive* otherCollisionPrimitive)
{
	assert(1); /// Not Implemented
}

bool LineCollisionPrimitive::IntersectCylinder(CylinderCollisionPrimitive* otherCollisionPrimitive)
{
	assert(1); /// Not Implemented
}

bool LineCollisionPrimitive::IntersectSphere(SphereCollisionPrimitive* otherCollisionPrimitive)
{
	assert(1); /// Not Implemented
}