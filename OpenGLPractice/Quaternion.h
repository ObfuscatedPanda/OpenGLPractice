#pragma once
#include "ProgramObject.h"
#include "Vector.h"
class Quaternion :
	public ProgramObject
{
private:
	float x;
	float y;
	float z;
	float w;

public:
	Quaternion(void);  ~Quaternion(void);
	inline float X() { return x; }
	inline float Y() { return y; }
	inline float Z() { return z; }
	inline float W() { return w; }

	inline float SetX(float _x) { x = _x; }
	inline float SetY(float _y) { y = _y; }
	inline float SetZ(float _z) { z = _z; }
	inline float SetW(float _w) { w = _w; }
	
	Quaternion & operator*(const Quaternion &rhs);

	void Normalize();
};

