#pragma once
#include "programobject.h"
class Interval :
	public ProgramObject
{
private:
	SCALAR a;
	SCALAR b;

public:
	Interval(void);
	~Interval(void);
	Interval(SCALAR a, SCALAR b);
	inline void Update(SCALAR _a, SCALAR _b)	{ a = _a; b = _b; }
	inline SCALAR A(void)					{ return a; }
	inline SCALAR B(void)					{ return b; }
	inline void SetA(SCALAR _a)				{ a = _a; }
	inline void SetB(SCALAR _b)				{ b = _b; }
	inline Interval Copy(void)				{ Interval newCopy(a, b); return newCopy; }
};

