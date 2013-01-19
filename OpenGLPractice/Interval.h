#pragma once
#include "programobject.h"
class Interval :
	public ProgramObject
{
private:
	float a;
	float b;

public:
	Interval(void);
	~Interval(void);
	Interval(float a, float b);
	inline void Update(float _a, float _b)	{ a = _a; b = _b; }
	inline float A(void)					{ return a; }
	inline float B(void)					{ return b; }
	inline void SetA(float _a)				{ a = _a; }
	inline void SetB(float _b)				{ b = _b; }
	inline Interval Copy(void)				{ Interval newCopy(a, b); return newCopy; }
};

