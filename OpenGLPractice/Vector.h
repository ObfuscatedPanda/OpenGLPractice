
#include "ProgramObject.h"

#ifndef VECTOR_H
#define VECTOR_H

#define _X 0
#define _Y 1
#define _Z 2

class Vector :
	public ProgramObject
{
private:
	
	/*
	float x;
	float y;
	float z;
	*/

public:
	Vector(void);
	~Vector(void);
	virtual float X(void) = 0;
	virtual float Y(void) = 0;
	virtual float Z(void) = 0;
	virtual float Magnitude(void) = 0;
	virtual void SetX(float _x) = 0;
	virtual void SetY(float _y) = 0;
	virtual void SetZ(float _z) = 0;
	virtual void Set(float _x, float _y, float _z) = 0;
	virtual void SetOrdinate(char ordinateNumber, float ordinateValue) = 0;

	virtual void Normalize() = 0;
	virtual float SumOfSquaredComponents() = 0;
};

#endif