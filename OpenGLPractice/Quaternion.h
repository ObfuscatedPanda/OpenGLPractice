#pragma once
#include "ProgramObject.h"
#include "Vector.h"
class Quaternion :
	public ProgramObject
{
private:
	SCALAR x;
	SCALAR y;
	SCALAR z;
	SCALAR w;

public:
	Quaternion(void);  ~Quaternion(void);
	inline SCALAR X() { return x; }
	inline SCALAR Y() { return y; }
	inline SCALAR Z() { return z; }
	inline SCALAR W() { return w; }

	inline SCALAR SetX(SCALAR _x) { x = _x; }
	inline SCALAR SetY(SCALAR _y) { y = _y; }
	inline SCALAR SetZ(SCALAR _z) { z = _z; }
	inline SCALAR SetW(SCALAR _w) { w = _w; }
	
	Quaternion & operator*(const Quaternion &rhs);

	void Normalize();
};

