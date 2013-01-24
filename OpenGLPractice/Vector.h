
#include "ProgramObject.h"

#ifndef Vector_H
#define Vector_H

#define _X 0
#define _Y 1
#define _Z 2

class Vector :
	public ProgramObject
{
public:

SCALAR x,y,z;	//x,y,z coordinates


Vector() : x(0), y(0), z(0)
{}

Vector( const SCALAR& a, const SCALAR& b, const SCALAR& c ) : x(a), y(b), z(c)
{}

//index a component
//NOTE: returning a reference allows
//you to assign the indexed element
inline SCALAR& operator [] ( const long i )
{
	return *((&x) + i);
}


inline const bool operator == ( const Vector& v ) const
{
	return (v.x == x && v.y == y && v.z == z);
}

inline const bool operator != ( const Vector& v ) const
{
	return !(v == *this);
}


inline const Vector operator - () const
{
	return Vector( -x, -y, -z );
}


inline const Vector& operator = ( const Vector& v )
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}



inline const Vector& operator += ( const Vector& v )
{
	x+=v.x;
	y+=v.y;
	z+=v.z;
	return *this;
}


inline const Vector& operator -= ( const Vector& v )
{
	x-=v.x;
	y-=v.y;
	z-=v.z;
	return *this;
}



inline const Vector& operator *= ( const SCALAR& s )
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}


inline const Vector& operator /= ( const SCALAR& s )
{
	const SCALAR r = 1 / s;
	x *= r;
	y *= r;
	z *= r;
	return *this;
}


inline const Vector operator + ( const Vector& v ) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}


inline const Vector operator - ( const Vector& v ) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}


inline const Vector operator * ( const SCALAR& s ) const
{
	return Vector( x * s, y * s, z * s );
}



friend inline const Vector operator * ( const SCALAR& s, const Vector& v )
{
	return v * s;
}



inline const Vector operator / (SCALAR s) const
{
	s = 1/s;
	return Vector( s * x, s * y, s * z );
}

//cross product

inline const Vector Cross( const Vector& v ) const
{
	return Vector( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x );
}



inline const SCALAR Dot( const Vector& v ) const
{
	return x * v.x + y * v.y + z * v.z;
}


inline const SCALAR LengthSquared() const
{
	return (SCALAR)this->Dot(*this);
}


inline const SCALAR Length() const
{
	return (SCALAR)sqrt( (double)this->Dot(*this) );
}



inline const Vector Unit() const
{
	return (*this) / Length();
}



inline void Normalize()
{
	(*this) /= Length();
}

//equal within an error ‘e’

inline const bool NearlyEquals( const Vector& v, const SCALAR e ) const
{
	return fabs(x - v.x);
}

};

//
// Position Vector
//

typedef Vector	POINT;
};

#endif