#pragma once
#include "Vector.h"
class Vector2d :
	public Vector
{
private:
	SCALAR ordinates[2];

public:
	Vector2d(void);
	~Vector2d(void);


	Vector2d(SCALAR _x, SCALAR _y);
	inline SCALAR X(void) { return ordinates[_X]; }
	inline SCALAR Y(void) { return ordinates[_Y]; }
	inline SCALAR Z(void) { return 0; }
	inline SCALAR Magnitude(void) { return sqrt((ordinates[_X] * ordinates[_X]) + (ordinates[_Y] * ordinates[_Y])); }
	inline void SetX(SCALAR _x) { ordinates[_X] = _x; }
	inline void SetY(SCALAR _y) { ordinates[_Y] = _y; }
	inline void SetZ(SCALAR _z) { SCALAR z = 0; }
	inline void Set(SCALAR _x, SCALAR _y, SCALAR _z=0) { ordinates[_X] = _x; ordinates[_Y] = _y; }
	inline void SetOrdinate(char ordinateNumber, SCALAR ordinateValue) 
	{	
		if(_X <= ordinateNumber && ordinateNumber <= _Y)
		{
			ordinates[ordinateNumber] = ordinateValue;
		}
	}
	
	void Normalize();
	SCALAR SumOfSquaredComponents() { return (ordinates[_X]*ordinates[_X]) + (ordinates[_Y]*ordinates[_Y]); }
};

