#pragma once
#include "Vector.h"
class Vector3d :
	public Vector
{
private:
	float ordinates[3];

public:
	Vector3d(void);
	~Vector3d(void);

	Vector3d(float _x, float _y, float _z);
	inline float X(void) { return ordinates[_X]; }
	inline float Y(void) { return ordinates[_Y]; }
	inline float Z(void) { return ordinates[_Z]; }
	inline float Magnitude(void) { return sqrt((ordinates[_X] * ordinates[_X]) + (ordinates[_Y] * ordinates[_Y]) + (ordinates[_Z] * ordinates[_Z])); }
	inline void SetX(float _x) { ordinates[_X] = _x; }
	inline void SetY(float _y) { ordinates[_Y] = _y; }
	inline void SetZ(float _z) { ordinates[_Z] = _z; }
	inline void Set(float _x, float _y, float _z) { ordinates[_X] = _x; ordinates[_Y] = _y; ordinates[_Z] = _z; }
	inline void SetOrdinate(char ordinateNumber, float ordinateValue) 
	{	if(_X <= ordinateNumber && ordinateNumber <= _Z)
		{
			ordinates[ordinateNumber] = ordinateValue;
		}
	}


	void Normalize();
	inline float SumOfSquaredComponents() { return (ordinates[_X]*ordinates[_X]) + (ordinates[_Y]*ordinates[_Y]) + (ordinates[_Z]*ordinates[_Z]); }
};

