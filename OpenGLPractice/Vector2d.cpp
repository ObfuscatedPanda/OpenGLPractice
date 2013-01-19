#include "Vector2d.h"


Vector2d::Vector2d(void)
{
	ordinates[_X] = 0;
	ordinates[_Y] = 0;
}


Vector2d::~Vector2d(void)
{
}

Vector2d::Vector2d(float _x, float _y = 0)
{
	ordinates[_X] = _x;
	ordinates[_Y] = _y;
}

void Vector2d::Normalize()
{
	float magnitude = sqrt(SumOfSquaredComponents());
	ordinates[_X] /= magnitude;
	ordinates[_Y] /= magnitude;
}

