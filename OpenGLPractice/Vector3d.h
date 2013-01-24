#pragma once
#include "Vector.h"
class Vector3d :
	public Vector
{
private:
	SCALAR ordinates[3];

public:
	Vector3d(void);
	~Vector3d(void);

	Vector3d(SCALAR _x, SCALAR _y, SCALAR _z);
	inline SCALAR X(void) { return ordinates[_X]; }
	inline SCALAR Y(void) { return ordinates[_Y]; }
	inline SCALAR Z(void) { return ordinates[_Z]; }
	inline SCALAR Magnitude(void) { return sqrt((ordinates[_X] * ordinates[_X]) + (ordinates[_Y] * ordinates[_Y]) + (ordinates[_Z] * ordinates[_Z])); }
	inline void SetX(SCALAR _x) { ordinates[_X] = _x; }
	inline void SetY(SCALAR _y) { ordinates[_Y] = _y; }
	inline void SetZ(SCALAR _z) { ordinates[_Z] = _z; }
	inline void Set(SCALAR _x, SCALAR _y, SCALAR _z) { ordinates[_X] = _x; ordinates[_Y] = _y; ordinates[_Z] = _z; }
	inline void SetOrdinate(char ordinateNumber, SCALAR ordinateValue) 
	{	if(_X <= ordinateNumber && ordinateNumber <= _Z)
		{
			ordinates[ordinateNumber] = ordinateValue;
		}
	}


	void Normalize();
	inline SCALAR SumOfSquaredComponents() { return (ordinates[_X]*ordinates[_X]) + (ordinates[_Y]*ordinates[_Y]) + (ordinates[_Z]*ordinates[_Z]); }
};

