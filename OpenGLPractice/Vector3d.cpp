#include "Vector3d.h"


Vector3d::Vector3d(void)
{
	ordinates[_X] = 0;
	ordinates[_Y] = 0;
	ordinates[_Z] = 0;
}

Vector3d::Vector3d(float _x, float _y = 0, float _z = 0)
{
	ordinates[_X] = _x;
	ordinates[_Y] = _y;
	ordinates[_Z] = _z;
}

Vector3d::~Vector3d(void)
{
}



void Vector3d::Normalize()
{
	float magnitude = sqrt(SumOfSquaredComponents());
	ordinates[_X] /= magnitude;
	ordinates[_Y] /= magnitude;
	ordinates[_Z] /= magnitude; 
}
