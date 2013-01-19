#pragma once
#include "Vector.h"
class Vector2d :
	public Vector
{
private:
	float ordinates[2];

public:
	Vector2d(void);
	~Vector2d(void);


	Vector2d(float _x, float _y);
	inline float X(void) { return ordinates[_X]; }
	inline float Y(void) { return ordinates[_Y]; }
	inline float Z(void) { return 0; }
	inline float Magnitude(void) { return sqrt((ordinates[_X] * ordinates[_X]) + (ordinates[_Y] * ordinates[_Y])); }
	inline void SetX(float _x) { ordinates[_X] = _x; }
	inline void SetY(float _y) { ordinates[_Y] = _y; }
	inline void SetZ(float _z) { float z = 0; }
	inline void Set(float _x, float _y, float _z=0) { ordinates[_X] = _x; ordinates[_Y] = _y; }
	inline void SetOrdinate(char ordinateNumber, float ordinateValue) 
	{	
		if(_X <= ordinateNumber && ordinateNumber <= _Y)
		{
			ordinates[ordinateNumber] = ordinateValue;
		}
	}
	
	void Normalize();
	float SumOfSquaredComponents() { return (ordinates[_X]*ordinates[_X]) + (ordinates[_Y]*ordinates[_Y]); }
};

