#include "Quaternion.h"


Quaternion::Quaternion(void)
{
	w = 0;
	x = 0;
	y = 0;
	z = 0;
}


Quaternion::~Quaternion(void)
{
}

void Quaternion::Normalize()
{
	SCALAR magnitude = sqrt((w*w) + (x*x) + (y*y) + (z*z));
	w /= magnitude;
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

Quaternion & Quaternion::operator*(const Quaternion &rhs)
{
	this->w =	(this->w * rhs.w) - 
				(this->x * rhs.x) - 
				(this->y * rhs.y) - 
				(this->z * rhs.z);
	this->x	=	(this->w * rhs.x) - 
				(this->x * rhs.w) - 
				(this->y * rhs.y) - 
				(this->z * rhs.z);
	this->y	=	(this->w * rhs.x) - 
				(this->x * rhs.z) - 
				(this->y * rhs.w) - 
				(this->z * rhs.x);
	this->z	=	(this->w * rhs.z) - 
				(this->x * rhs.y) - 
				(this->y * rhs.x) - 
				(this->z * rhs.w);
	return *this;
}