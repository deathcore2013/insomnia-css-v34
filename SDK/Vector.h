#ifndef __VECTOR_H__
#define __VECTOR_H__

#pragma once

#include <math.h>
#include <float.h>
#include <cstdlib>

#define X_INDEX	0
#define Y_INDEX	1
#define Z_INDEX	2

#ifndef M_PI
#define M_PI			3.14159265358979323846
#endif

#define M_PI_F		((float)(M_PI))

#ifndef RAD2DEG
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif
typedef float vec_t;
class Vector;
class Vector2D;

class Vector2D
{
public:
	Vector2D(float X, float Y)
	{
		x=X;
		y=Y;
	}
	Vector2D()
	{
		x=y=0.f;
	}
	float x, y;
};

//=========================================================
// 3D Vector
//=========================================================
class Vector					
{
public:
	// Members
	float x, y, z;

	// Construction/destruction:
	Vector(void); 
	Vector(float X, float Y, float Z);
	explicit Vector(float XYZ); ///< broadcast initialize

	// Initialization
	void Init(float ix=0.0f, float iy=0.0f, float iz=0.0f);

	bool IsValid() const;
	void Invalidate();

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	Vector2D& AsVector2D();
	const Vector2D& AsVector2D() const;
		
	// Initialization methods
	void Random( float minVal, float maxVal );
	inline void Zero(); ///< zero out a vector

	// equality
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;	

	// arithmetic operations
	inline Vector&	operator+=(const Vector &v);			
	inline Vector&	operator-=(const Vector &v);		
	inline Vector&	operator*=(const Vector &v);			
	inline Vector&	operator*=(float s);
	inline Vector&	operator/=(const Vector &v);		
	inline Vector&	operator/=(float s);	
	inline Vector&	operator+=(float fl) ; ///< broadcast add
	inline Vector&	operator-=(float fl) ; ///< broadcast sub			

// negate the vector components
	void	Negate(); 

	// Get the vector's magnitude.
	inline float	Length() const;

	// Get the vector's magnitude squared.
	inline float LengthSqr(void) const
	{
		return (x*x + y*y + z*z);		
	}

	// return true if this vector is (0,0,0) within tolerance
	bool IsZero( float tolerance = 0.01f ) const
	{
		return (x > -tolerance && x < tolerance &&
				y > -tolerance && y < tolerance &&
				z > -tolerance && z < tolerance);
	}

	float	NormalizeInPlace();
	Vector	Normalized() const;
	bool	IsLengthGreaterThan( float val ) const;
	bool	IsLengthLessThan( float val ) const;

	// check if a vector is within the box defined by two other vectors
	inline bool WithinAABox( Vector const &boxmin, Vector const &boxmax);
 
	// Get the distance from this vector to the other one.
	float	DistTo(const Vector &vOther) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' inline.  
	// may be able to tidy this up after switching to VC7
	inline float DistToSqr(const Vector &vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}

	// Copy
	void	CopyToArray(float* rgfl) const;	

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void	MulAdd(const Vector& a, const Vector& b, float scalar);	

	// Dot product.
	float	Dot(const Vector& vOther) const;			

	// assignment
	Vector& operator=(const Vector &vOther);

	// 2d
	float	Length2D(void) const;					
	float	Length2DSqr(void) const;					



	Vector(const Vector &vOther);

	// arithmetic operations
	Vector	operator-(void) const;
				
	Vector	operator+(const Vector& v) const;	
	Vector	operator-(const Vector& v) const;	
	Vector	operator*(const Vector& v) const;	
	Vector	operator/(const Vector& v) const;	
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;			
	
	// Cross product between two vectors.
	Vector	Cross(const Vector &vOther) const;		

	// Returns a vector with the min or max in X, Y, and Z.
	Vector	Min(const Vector &vOther) const;
	Vector	Max(const Vector &vOther) const;


};

//-----------------------------------------------------------------------------
// Allows us to specifically pass the vector by value when we need to
//-----------------------------------------------------------------------------
class VectorByValue : public Vector
{
public:
	// Construction/destruction:
	VectorByValue(void) : Vector() {} 
	VectorByValue(float X, float Y, float Z) : Vector( X, Y, Z ) {}
	VectorByValue(const VectorByValue& vOther) { *this = vOther; }
};

//-----------------------------------------------------------------------------
// Here's where we add all those lovely SSE optimized routines
//-----------------------------------------------------------------------------

class __declspec(align(16)) VectorAligned: public Vector
{
public:
	inline VectorAligned(void) {};
	inline VectorAligned(float X, float Y, float Z) 
	{
		Init(X,Y,Z);
	}

public:
	explicit VectorAligned(const Vector &vOther) 
	{
		Init(vOther.x, vOther.y, vOther.z);
	}
	
	VectorAligned& operator=(const Vector &vOther)	
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}
	float w;	// this space is used anyway
};

//-----------------------------------------------------------------------------
// Vector related operations
//-----------------------------------------------------------------------------

// Vector clear
void VectorClear( Vector& a );

// Copy
void VectorCopy( const Vector& src, Vector& dst );

// Vector arithmetic
void VectorAdd( const Vector& a, const Vector& b, Vector& result );
void VectorSubtract( const Vector& a, const Vector& b, Vector& result );
void VectorMultiply( const Vector& a, vec_t b, Vector& result );
void VectorMultiply( const Vector& a, const Vector& b, Vector& result );
void VectorDivide( const Vector& a, vec_t b, Vector& result );
void VectorDivide( const Vector& a, const Vector& b, Vector& result );
void VectorScale ( const Vector& in, vec_t scale, Vector& result );
// Don't mark this as inline in its function declaration. That's only necessary on its
// definition, and 'inline' here leads to gcc warnings.
void VectorMA( const Vector& start, float scale, const Vector& direction, Vector& dest );

// Vector equality with tolerance
bool VectorsAreEqual( const Vector& src1, const Vector& src2, float tolerance = 0.0f );

#define VectorExpand(v) (v).x, (v).y, (v).z


// Normalization
// FIXME: Can't use quite yet
//vec_t VectorNormalize( Vector& v );

// Length
inline vec_t VectorLength( const Vector& v );

// Dot Product
inline vec_t DotProduct(const Vector& a, const Vector& b);

// Cross product
void CrossProduct(const Vector& a, const Vector& b, Vector& result );

// Store the min or max of each of x, y, and z into the result.
void VectorMin( const Vector &a, const Vector &b, Vector &result );
void VectorMax( const Vector &a, const Vector &b, Vector &result );

// Linearly interpolate between two vectors
void VectorLerp(const Vector& src1, const Vector& src2, vec_t t, Vector& dest );
Vector VectorLerp(const Vector& src1, const Vector& src2, vec_t t );

inline Vector ReplicateToVector( float x )
{
	return Vector( x, x, x );
}

// check if a point is in the field of a view of an object. supports up to 180 degree fov.
inline bool PointWithinViewAngle( Vector const &vecSrcPosition, 
										Vector const &vecTargetPosition, 
										Vector const &vecLookDirection, float flCosHalfFOV )
{
	Vector vecDelta = vecTargetPosition - vecSrcPosition;
	float cosDiff = DotProduct( vecLookDirection, vecDelta );

	if ( cosDiff < 0 ) 
		return false;

	float flLen2 = vecDelta.LengthSqr();

	// a/sqrt(b) > c  == a^2 > b * c ^2
	return ( cosDiff * cosDiff > flLen2 * flCosHalfFOV * flCosHalfFOV );
	
}

// Cross product
Vector CrossProduct( const Vector& a, const Vector& b );

// Random vector creation
Vector RandomVector( vec_t minVal, vec_t maxVal );


float RandomVectorInUnitSphere( Vector *pVector );
float RandomVectorInUnitCircle( Vector2D *pVector );


//-----------------------------------------------------------------------------
//
// Inlined Vector methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline Vector::Vector(void)									
{ 

}

inline Vector::Vector(vec_t X, vec_t Y, vec_t Z)						
{ 
	x = X; y = Y; z = Z;
}

inline Vector::Vector(vec_t XYZ)						
{ 
	x = y = z = XYZ;
}

inline Vector::Vector(const Vector &vOther)					
{ 
	x = vOther.x; y = vOther.y; z = vOther.z;
}

inline void Vector::Init( vec_t ix, vec_t iy, vec_t iz )    
{ 
	x = ix; y = iy; z = iz;
}

inline void Vector::Random( vec_t minVal, vec_t maxVal )
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

// This should really be a single opcode on the PowerPC (move r0 onto the vec reg)
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}

inline void VectorClear( Vector& a )
{
	a.x = a.y = a.z = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector& Vector::operator=(const Vector &vOther)	
{
	x=vOther.x; y=vOther.y; z=vOther.z; 
	return *this; 
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline vec_t& Vector::operator[](int i)
{
	return ((vec_t*)this)[i];
}

inline vec_t Vector::operator[](int i) const
{
	return ((vec_t*)this)[i];
}


//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline vec_t* Vector::Base()
{
	return (vec_t*)this;
}

inline vec_t const* Vector::Base() const
{
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// Cast to Vector2D...
//-----------------------------------------------------------------------------

inline Vector2D& Vector::AsVector2D()
{
	return *(Vector2D*)this;
}

inline const Vector2D& Vector::AsVector2D() const
{
	return *(const Vector2D*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

inline bool Vector::IsValid() const
{
	return true;
}

//-----------------------------------------------------------------------------
// Invalidate
//-----------------------------------------------------------------------------

inline void Vector::Invalidate()
{
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector::operator==( const Vector& src ) const
{
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool Vector::operator!=( const Vector& src ) const
{
	return (src.x != x) || (src.y != y) || (src.z != z);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void VectorCopy( const Vector& src, Vector& dst )
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

inline void	Vector::CopyToArray(float* rgfl) const		
{
	rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; 
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
// #pragma message("TODO: these should be SSE")

inline void Vector::Negate()
{
	x = -x; y = -y; z = -z; 
} 

inline  Vector& Vector::operator+=(const Vector& v)	
{
	x+=v.x; y+=v.y; z += v.z;	
	return *this;
}

inline  Vector& Vector::operator-=(const Vector& v)	
{ 
	x-=v.x; y-=v.y; z -= v.z;	
	return *this;
}

inline  Vector& Vector::operator*=(float fl)	
{
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

inline  Vector& Vector::operator*=(const Vector& v)	
{ 
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

// this ought to be an opcode.
inline Vector&	Vector::operator+=(float fl) 
{
	x += fl;
	y += fl;
	z += fl;
	return *this;
}

inline Vector&	Vector::operator-=(float fl) 
{
	x -= fl;
	y -= fl;
	z -= fl;
	return *this;
}



inline  Vector& Vector::operator/=(float fl)	
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

inline  Vector& Vector::operator/=(const Vector& v)	
{ 
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}




inline void VectorAdd( const Vector& a, const Vector& b, Vector& c )
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

inline void VectorSubtract( const Vector& a, const Vector& b, Vector& c )
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

inline void VectorMultiply( const Vector& a, vec_t b, Vector& c )
{
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
}

inline void VectorMultiply( const Vector& a, const Vector& b, Vector& c )
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
}

// for backwards compatability
inline void VectorScale ( const Vector& in, vec_t scale, Vector& result )
{
	VectorMultiply( in, scale, result );
}


inline void VectorDivide( const Vector& a, vec_t b, Vector& c )
{
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
	c.z = a.z * oob;
}

inline void VectorDivide( const Vector& a, const Vector& b, Vector& c )
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
	c.z = a.z / b.z;
}

inline void	Vector::MulAdd(const Vector& a, const Vector& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
	z = a.z + b.z * scalar;
}

inline void VectorLerp(const Vector& src1, const Vector& src2, vec_t t, Vector& dest )
{
	dest.x = src1.x + (src2.x - src1.x) * t;
	dest.y = src1.y + (src2.y - src1.y) * t;
	dest.z = src1.z + (src2.z - src1.z) * t;
}

inline Vector VectorLerp(const Vector& src1, const Vector& src2, vec_t t )
{
	Vector result;
	VectorLerp( src1, src2, t, result );
	return result;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
inline vec_t DotProduct(const Vector& a, const Vector& b) 
{ 
	return( a.x*b.x + a.y*b.y + a.z*b.z ); 
}

// for backwards compatability
inline vec_t Vector::Dot( const Vector& vOther ) const
{
	return DotProduct( *this, vOther );
}

inline void CrossProduct(const Vector& a, const Vector& b, Vector& result )
{
	result.x = a.y*b.z - a.z*b.y;
	result.y = a.z*b.x - a.x*b.z;
	result.z = a.x*b.y - a.y*b.x;
}

inline vec_t DotProductAbs( const Vector &v0, const Vector &v1 )
{
	return fabs(v0.x*v1.x) + fabs(v0.y*v1.y) + fabs(v0.z*v1.z);
}

inline vec_t DotProductAbs( const Vector &v0, const float *v1 )
{
	return fabs(v0.x * v1[0]) + fabs(v0.y * v1[1]) + fabs(v0.z * v1[2]);
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline vec_t VectorLength( const Vector& v )
{
	return (vec_t)sqrt(v.x*v.x + v.y*v.y + v.z*v.z);		
}


inline vec_t Vector::Length(void) const	
{
	return VectorLength( *this );
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------

/*
// FIXME: Can't use until we're un-macroed in mathlib.h
inline vec_t VectorNormalize( Vector& v )
{
	Assert( v.IsValid() );
	vec_t l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		// FIXME: 
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
*/


// check a point against a box
bool Vector::WithinAABox( Vector const &boxmin, Vector const &boxmax)
{
	return ( 
		( x >= boxmin.x ) && ( x <= boxmax.x) &&
		( y >= boxmin.y ) && ( y <= boxmax.y) &&
		( z >= boxmin.z ) && ( z <= boxmax.z)
		);
}

//-----------------------------------------------------------------------------
// Get the distance from this vector to the other one 
//-----------------------------------------------------------------------------
inline vec_t Vector::DistTo(const Vector &vOther) const
{
	Vector delta;
	VectorSubtract( *this, vOther, delta );
	return delta.Length();
}


//-----------------------------------------------------------------------------
// Vector equality with tolerance
//-----------------------------------------------------------------------------
inline bool VectorsAreEqual( const Vector& src1, const Vector& src2, float tolerance )
{
	if (fabs(src1.x - src2.x) > tolerance)
		return false;
	if (fabs(src1.y - src2.y) > tolerance)
		return false;
	return (fabs(src1.z - src2.z) <= tolerance);
}


//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint( const Vector& vecStart, float flMaxDist, const Vector& vecTarget, Vector *pResult )
{
	Vector vecDelta;
	VectorSubtract( vecTarget, vecStart, vecDelta );
	float flDistSqr = vecDelta.LengthSqr();
	if ( flDistSqr <= flMaxDist * flMaxDist )
	{
		*pResult = vecTarget;
	}
	else
	{
		vecDelta /= sqrt( flDistSqr );
		VectorMA( vecStart, flMaxDist, vecDelta, *pResult );
	}
}


//-----------------------------------------------------------------------------
// Takes the absolute value of a vector
//-----------------------------------------------------------------------------
inline void VectorAbs( const Vector& src, Vector& dst )
{
	dst.x = fabs(src.x);
	dst.y = fabs(src.y);
	dst.z = fabs(src.z);
}



//-----------------------------------------------------------------------------
// Returns a vector with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------
inline Vector Vector::Min(const Vector &vOther) const
{
	return Vector(x < vOther.x ? x : vOther.x, 
		y < vOther.y ? y : vOther.y, 
		z < vOther.z ? z : vOther.z);
}

inline Vector Vector::Max(const Vector &vOther) const
{
	return Vector(x > vOther.x ? x : vOther.x, 
		y > vOther.y ? y : vOther.y, 
		z > vOther.z ? z : vOther.z);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline Vector Vector::operator-(void) const
{ 
	return Vector(-x,-y,-z);				
}

inline Vector Vector::operator+(const Vector& v) const	
{ 
	Vector res;
	VectorAdd( *this, v, res );
	return res;	
}

inline Vector Vector::operator-(const Vector& v) const	
{ 
	Vector res;
	VectorSubtract( *this, v, res );
	return res;	
}

inline Vector Vector::operator*(float fl) const	
{ 
	Vector res;
	VectorMultiply( *this, fl, res );
	return res;	
}

inline Vector Vector::operator*(const Vector& v) const	
{ 
	Vector res;
	VectorMultiply( *this, v, res );
	return res;	
}

inline Vector Vector::operator/(float fl) const	
{ 
	Vector res;
	VectorDivide( *this, fl, res );
	return res;	
}

inline Vector Vector::operator/(const Vector& v) const	
{ 
	Vector res;
	VectorDivide( *this, v, res );
	return res;	
}

inline Vector operator*(float fl, const Vector& v)	
{ 
	return v * fl; 
}

//-----------------------------------------------------------------------------
// cross product
//-----------------------------------------------------------------------------

inline Vector Vector::Cross(const Vector& vOther) const
{ 
	Vector res;
	CrossProduct( *this, vOther, res );
	return res;
}

//-----------------------------------------------------------------------------
// 2D
//-----------------------------------------------------------------------------

inline vec_t Vector::Length2D(void) const
{ 
	return (vec_t)sqrtf(x*x + y*y); 
}

inline vec_t Vector::Length2DSqr(void) const
{ 
	return (x*x + y*y); 
}

inline Vector CrossProduct(const Vector& a, const Vector& b) 
{ 
	return Vector( a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x ); 
}

inline void VectorMin( const Vector &a, const Vector &b, Vector &result )
{
	result.x = min(a.x, b.x);
	result.y = min(a.y, b.y);
	result.z = min(a.z, b.z);
}

inline void VectorMax( const Vector &a, const Vector &b, Vector &result )
{
	result.x = max(a.x, b.x);
	result.y = max(a.y, b.y);
	result.z = max(a.z, b.z);
}

inline float ComputeVolume( const Vector &vecMins, const Vector &vecMaxs )
{
	Vector vecDelta;
	VectorSubtract( vecMaxs, vecMins, vecDelta );
	return DotProduct( vecDelta, vecDelta );
}

// Get a random vector.
inline Vector RandomVector( float minVal, float maxVal )
{
	Vector random;
	random.Random( minVal, maxVal );
	return random;
}

//-----------------------------------------------------------------------------
// Radian Euler angle aligned to axis (NOT ROLL/PITCH/YAW)
//-----------------------------------------------------------------------------
class QAngle;
class RadianEuler
{
public:
	inline RadianEuler(void)							{ }
	inline RadianEuler(float X, float Y, float Z)		{ x = X; y = Y; z = Z; }
	inline RadianEuler(QAngle const &angles);	// evil auto type promotion!!!

	// Initialization
	inline void Init(float ix=0.0f, float iy=0.0f, float iz=0.0f)	{ x = ix; y = iy; z = iz; }

	//	conversion to qangle
	QAngle ToQAngle( void ) const;
	bool IsValid() const;
	void Invalidate();

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	float x, y, z;
};


inline void VectorCopy( RadianEuler const& src, RadianEuler &dst )
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

inline void VectorScale( RadianEuler const& src, float b, RadianEuler &dst )
{
	dst.x = src.x * b;
	dst.y = src.y * b;
	dst.z = src.z * b;
}

inline bool RadianEuler::IsValid() const
{
	return true;
}

inline void RadianEuler::Invalidate()
{
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& RadianEuler::operator[](int i)
{
	return ((float*)this)[i];
}

inline float RadianEuler::operator[](int i) const
{
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// Degree Euler QAngle pitch, yaw, roll
//-----------------------------------------------------------------------------
class QAngleByValue;

class QAngle					
{
public:
	// Members
	float x, y, z;

	// Construction/destruction
	QAngle(void);
	QAngle(float X, float Y, float Z);
//	QAngle(RadianEuler const &angles);	// evil auto type promotion!!!

	// Allow pass-by-value
	operator QAngleByValue &()				{ return *((QAngleByValue *)(this)); }
	operator const QAngleByValue &() const	{ return *((const QAngleByValue *)(this)); }

	// Initialization
	void Init(float ix=0.0f, float iy=0.0f, float iz=0.0f);
	void Random( float minVal, float maxVal );

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;
	
	// equality
	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;	

	// arithmetic operations
	QAngle&	operator+=(const QAngle &v);
	QAngle&	operator-=(const QAngle &v);
	QAngle&	operator*=(float s);
	QAngle&	operator/=(float s);

	// Get the vector's magnitude.
	float	Length() const;
	float	LengthSqr() const;

	// negate the QAngle components
	//void	Negate(); 

	// No assignment operators either...
	QAngle& operator=( const QAngle& src );


	QAngle	operator-(void) const;
	
	QAngle	operator+(const QAngle& v) const;
	QAngle	operator-(const QAngle& v) const;
	QAngle	operator*(float fl) const;
	QAngle	operator/(float fl) const;

};

	
//-----------------------------------------------------------------------------
// Allows us to specifically pass the vector by value when we need to
//-----------------------------------------------------------------------------
class QAngleByValue : public QAngle
{
public:
	// Construction/destruction:
	QAngleByValue(void) : QAngle() {} 
	QAngleByValue(float X, float Y, float Z) : QAngle( X, Y, Z ) {}
	QAngleByValue(const QAngleByValue& vOther) { *this = vOther; }
};


inline void VectorAdd( const QAngle& a, const QAngle& b, QAngle& result )
{
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
}

inline void VectorMA( const QAngle &start, float scale, const QAngle &direction, QAngle &dest )
{
	dest.x = start.x + scale * direction.x;
	dest.y = start.y + scale * direction.y;
	dest.z = start.z + scale * direction.z;
}


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)									
{
}

inline QAngle::QAngle(float X, float Y, float Z)						
{ 
	x = X; y = Y; z = Z;
}


//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init( float ix, float iy, float iz )    
{ 
	x = ix; y = iy; z = iz;
}

inline void QAngle::Random( float minVal, float maxVal )
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);

}


inline QAngle RandomAngle( float minVal, float maxVal )
{
	Vector random;
	random.Random( minVal, maxVal );
	QAngle ret( random.x, random.y, random.z );
	return ret;
}



inline RadianEuler::RadianEuler(QAngle const &angles)
{
	Init(
		angles.z * 3.14159265358979323846f / 180.f,
		angles.x * 3.14159265358979323846f / 180.f, 
		angles.y * 3.14159265358979323846f / 180.f );
}




inline QAngle RadianEuler::ToQAngle( void) const
{
	return QAngle(
		y * 180.f / 3.14159265358979323846f,
		z * 180.f / 3.14159265358979323846f,
		x * 180.f / 3.14159265358979323846f );
}


//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle &vOther)	
{
	x=vOther.x; y=vOther.y; z=vOther.z; 
	return *this; 
}


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
	return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
	return ((float*)this)[i];
}


//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
	return (float*)this;
}

inline float const* QAngle::Base() const
{
	return (float const*)this;
}


//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------
inline bool QAngle::IsValid() const
{
	return true;
}

//-----------------------------------------------------------------------------
// Invalidate
//-----------------------------------------------------------------------------

inline void QAngle::Invalidate()
{
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==( const QAngle& src ) const
{
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=( const QAngle& src ) const
{
	return (src.x != x) || (src.y != y) || (src.z != z);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------
inline void VectorCopy( const QAngle& src, QAngle& dst )
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}


//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)	
{ 
	x+=v.x; y+=v.y; z += v.z;	
	return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)	
{ 
	x-=v.x; y-=v.y; z -= v.z;	
	return *this;
}

inline QAngle& QAngle::operator*=(float fl)	
{
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

inline QAngle& QAngle::operator/=(float fl)	
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length( ) const
{
	return (float)sqrt( LengthSqr( ) );		
}


inline float QAngle::LengthSqr( ) const
{
	return x * x + y * y + z * z;
}
	

//-----------------------------------------------------------------------------
// Vector equality with tolerance
//-----------------------------------------------------------------------------
inline bool QAnglesAreEqual( const QAngle& src1, const QAngle& src2, float tolerance = 0.0f )
{
	if (fabs(src1.x - src2.x) > tolerance)
		return false;
	if (fabs(src1.y - src2.y) > tolerance)
		return false;
	return (fabs(src1.z - src2.z) <= tolerance);
}



inline QAngle QAngle::operator-(void) const
{ 
	QAngle ret(-x,-y,-z);
	return ret;
}

inline QAngle QAngle::operator+(const QAngle& v) const	
{ 
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;	
}

inline QAngle QAngle::operator-(const QAngle& v) const	
{ 
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;	
}

inline QAngle QAngle::operator*(float fl) const	
{ 
	QAngle res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;	
}

inline QAngle QAngle::operator/(float fl) const	
{ 
	QAngle res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;	
}

inline QAngle operator*(float fl, const QAngle& v)	
{ 
		QAngle ret( v * fl );
	return ret;
}

inline float InvRSquared( float const *v )
{
	return 1.f/max(1.f, v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

inline float InvRSquared( const Vector &v )
{
	return InvRSquared(&v.x);
}

inline float VectorNormalize( Vector& vec )
{
	float sqrlen = vec.LengthSqr() + 1.0e-10f, invlen;
	invlen = 1.f / sqrt(sqrlen);
	vec.x *= invlen;
	vec.y *= invlen;
	vec.z *= invlen;
	return sqrlen * invlen;
}

inline void Normalize( QAngle& angles )
{
	int i;
	for( i = 0; i < 3; i++ )
	{
		if( angles[i] > 180.0 ) angles[i] -= 360.0;
		else if( angles[i] < -180.0 ) angles[i] += 360.0;
	}
}

inline float VectorNormalize( float * v )
{
	return VectorNormalize(*(reinterpret_cast<Vector *>(v)));
}

inline void VectorNormalizeFast( Vector &vec )
{
	VectorNormalize(vec);
}


inline float Vector::NormalizeInPlace()
{
	return VectorNormalize( *this );
}

inline Vector Vector::Normalized() const
{
	Vector norm = *this;
	VectorNormalize( norm );
	return norm;
}

inline bool Vector::IsLengthGreaterThan( float val ) const
{
	return LengthSqr() > val*val;
}

inline bool Vector::IsLengthLessThan( float val ) const
{
	return LengthSqr() < val*val;
}

inline void VectorVectors( const Vector &forward, Vector &right, Vector &up )
{
	Vector tmp;

	if (forward[0] == 0 && forward[1] == 0)
	{
		// pitch 90 degrees up/down from identity
		right[0] = 0;	
		right[1] = -1; 
		right[2] = 0;
		up[0] = -forward[2]; 
		up[1] = 0; 
		up[2] = 0;
	}
	else
	{
		tmp[0] = 0; tmp[1] = 0; tmp[2] = 1.0;
		CrossProduct( forward, tmp, right );
		VectorNormalize( right );
		CrossProduct( right, forward, up );
		VectorNormalize( up );
	}
}

class Quaternion				// same data-layout as engine's vec4_t,
{								//		which is a vec_t[4]
public:
	inline Quaternion(void)							{ }
	inline Quaternion(RadianEuler const &angle);	// evil auto type promotion!!!

	inline void Init(vec_t ix=0.0f, vec_t iy=0.0f, vec_t iz=0.0f, vec_t iw=0.0f)	{ x = ix; y = iy; z = iz; w = iw; }

	bool IsValid() const;

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	vec_t x, y, z, w;
};


//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline vec_t& Quaternion::operator[](int i)
{
	return ((vec_t*)this)[i];
}

inline vec_t Quaternion::operator[](int i) const
{
	return ((vec_t*)this)[i];
}

struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t( 
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23 )
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin )
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin )
	{
		Init( xAxis, yAxis, zAxis, vecOrigin );
	}

	inline void Invalidate( void )
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = 0.f;
			}
		}
	}

	float *operator[]( int i )				{ return m_flMatVal[i]; }
	const float *operator[]( int i ) const	{ return m_flMatVal[i]; }
	float *Base()							{ return &m_flMatVal[0][0]; }
	const float *Base() const				{ return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};

inline void MatrixAngles( const matrix3x4_t& matrix, float *angles )
{ 
	float forward[3];
	float left[3];
	float up[3];

	//
	// Extract the basis vectors from the matrix. Since we only need the Z
	// component of the up vector, we don't get X and Y.
	//
	forward[0] = matrix[0][0];
	forward[1] = matrix[1][0];
	forward[2] = matrix[2][0];
	left[0] = matrix[0][1];
	left[1] = matrix[1][1];
	left[2] = matrix[2][1];
	up[2] = matrix[2][2];

	float xyDist = sqrtf( forward[0] * forward[0] + forward[1] * forward[1] );
	
	// enough here to get angles?
	if ( xyDist > 0.001f )
	{
		// (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the X axis
		angles[1] = RAD2DEG( atan2f( forward[1], forward[0] ) );

		// The engine does pitch inverted from this, but we always end up negating it in the DLL
		// UNDONE: Fix the engine to make it consistent
		// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
		angles[0] = RAD2DEG( atan2f( -forward[2], xyDist ) );

		// (roll)	z = ATAN( left.z, up.z );
		angles[2] = RAD2DEG( atan2f( left[2], up[2] ) );
	}
	else	// forward is mostly Z, gimbal lock-
	{
		// (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
		angles[1] = RAD2DEG( atan2f( -left[0], left[1] ) );

		// The engine does pitch inverted from this, but we always end up negating it in the DLL
		// UNDONE: Fix the engine to make it consistent
		// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
		angles[0] = RAD2DEG( atan2f( -forward[2], xyDist ) );

		// Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
		angles[2] = 0;
	}
}

inline void MatrixGetColumn( const matrix3x4_t& in, int column, Vector &out )
{
	out.x = in[0][column];
	out.y = in[1][column];
	out.z = in[2][column];
}

inline void MatrixPosition( const matrix3x4_t &matrix, Vector &position )
{
	MatrixGetColumn( matrix, 3, position );
}

inline void MatrixAngles( const matrix3x4_t &matrix, QAngle &angles )
{
	MatrixAngles( matrix, &angles.x );
}

inline void MatrixAngles( const matrix3x4_t &matrix, QAngle &angles, Vector &position )
{
	MatrixAngles( matrix, angles );
	MatrixPosition( matrix, position );
}

struct VMatrix
{
	VMatrix() {}
	VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
		);

	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	VMatrix( const Vector& forward, const Vector& left, const Vector& up );
	VMatrix( const Vector& forward, const Vector& left, const Vector& up, const Vector& translation );
	
	// Construct from a 3x4 matrix
	VMatrix( const matrix3x4_t& matrix3x4 );

	// Set the values in the matrix.
	void		Init( 
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33 
		);


	// Initialize from a 3x4
	void		Init( const matrix3x4_t& matrix3x4 );

	// array access
	inline float* operator[](int i)
	{ 
		return m[i]; 
	}

	inline const float* operator[](int i) const
	{ 
		return m[i]; 
	}

	// Get a pointer to m[0][0]
	inline float *Base()
	{
		return &m[0][0];
	}

	inline const float *Base() const
	{
		return &m[0][0];
	}
	
	vec_t		m[4][4];	
};

template< class T >
class CUtlMemory
{
public:
	// constructor, destructor
	CUtlMemory( int nGrowSize = 0, int nInitSize = 0 );
	CUtlMemory( T* pMemory, int numElements );
	~CUtlMemory();

	// element access
	T& operator[]( int i );
	T const& operator[]( int i ) const;
	T& Element( int i );
	T const& Element( int i ) const;

	// Can we use this index?
	bool IsIdxValid( int i ) const;

	// Gets the base address (can change when adding elements!)
	T* Base();
	T const* Base() const;

	// Attaches the buffer to external memory....
	void SetExternalBuffer( T* pMemory, int numElements );

	// Size
	int NumAllocated() const;
	int Count() const;

	// Grows the memory, so that at least allocated + num elements are allocated
	void Grow( int num = 1 );

	// Makes sure we've got at least this much memory
	void EnsureCapacity( int num );

	// Memory deallocation
	void Purge();

	// is the memory externally allocated?
	bool IsExternallyAllocated() const;

	// Set the size by which the memory grows
	void SetGrowSize( int size );

protected:
	enum
	{
		EXTERNAL_BUFFER_MARKER = -1,
	};

	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template< class T, class A = CUtlMemory<T> >
class CUtlVector
{
	typedef A CAllocator;
public:
	typedef T ElemType_t;

	// constructor, destructor
	CUtlVector( int growSize = 0, int initSize = 0 );
	CUtlVector( T* pMemory, int numElements );
	~CUtlVector();
	
	// Copy the array.
	CUtlVector<T, A>& operator=( const CUtlVector<T, A> &other );

	// element access
	T& operator[]( int i );
	const T& operator[]( int i ) const;
	T& Element( int i );
	const T& Element( int i ) const;

	// Gets the base address (can change when adding elements!)
	T* Base()								{ return m_Memory.Base(); }
	const T* Base() const					{ return m_Memory.Base(); }
	
	// Returns the number of elements in the vector
	// SIZE IS DEPRECATED!
	int Count() const;
	int Size() const;	// don't use me!

	// Is element index valid?
	bool IsValidIndex( int i ) const;
	static int InvalidIndex( void );

	// Adds an element, uses default constructor
	int AddToHead();
	int AddToTail();
	int InsertBefore( int elem );
	int InsertAfter( int elem );

	// Adds an element, uses copy constructor
	int AddToHead( const T& src );
	int AddToTail( const T& src );
	int InsertBefore( int elem, const T& src );
	int InsertAfter( int elem, const T& src );

	// Adds multiple elements, uses default constructor
	int AddMultipleToHead( int num );
	int AddMultipleToTail( int num, const T *pToCopy=NULL );	   
	int InsertMultipleBefore( int elem, int num, const T *pToCopy=NULL );	// If pToCopy is set, then it's an array of length 'num' and
	int InsertMultipleAfter( int elem, int num );

	// Calls RemoveAll() then AddMultipleToTail.
	void SetSize( int size );
	void SetCount( int count );
	
	// Calls SetSize and copies each element.
	void CopyArray( const T *pArray, int size );
	
	// Add the specified array to the tail.
	int AddVectorToTail( CUtlVector<T, A> const &src );

	// Finds an element (element needs operator== defined)
	int Find( const T& src ) const;

	bool HasElement( const T& src ) const;

	// Makes sure we have enough memory allocated to store a requested # of elements
	void EnsureCapacity( int num );

	// Makes sure we have at least this many elements
	void EnsureCount( int num );

	// Element removal
	void FastRemove( int elem );	// doesn't preserve order
	void Remove( int elem );		// preserves order, shifts elements
	void FindAndRemove( const T& src );	// removes first occurrence of src, preserves order, shifts elements
	void RemoveMultiple( int elem, int num );	// preserves order, shifts elements
	void RemoveAll();				// doesn't deallocate memory

	// Memory deallocation
	void Purge();

	// Purges the list and calls delete on each element in it.
	void PurgeAndDeleteElements();

	// Set the size by which it grows when it needs to allocate more memory.
	void SetGrowSize( int size )			{ m_Memory.SetGrowSize( size ); }

	int NumAllocated() const;	// Only use this if you really know what you're doing!

	void Sort( int (*pfnCompare)(const T *, const T *) );

protected:
	// Can't copy this unless we explicitly do it!
	CUtlVector( CUtlVector const& vec ) { Assert(0); }

	// Grows the vector
	void GrowVector( int num = 1 );

	// Shifts elements....
	void ShiftElementsRight( int elem, int num = 1 );
	void ShiftElementsLeft( int elem, int num = 1 );

	// For easier access to the elements through the debugger
	void ResetDbgInfo();

	CAllocator m_Memory;
	int m_Size;

	// For easier access to the elements through the debugger
	// it's in release builds so this can be used in libraries correctly
	T *m_pElements;
};

FORCEINLINE float DotProduct( const float *v1,const float *v2 )
{
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}
FORCEINLINE void VectorTransform( const float *in1,const matrix3x4_t & in2, float *out )
{
	out[0] = DotProduct(in1, in2[0]) + in2[0][3];
	out[1] = DotProduct(in1, in2[1]) + in2[1][3];
	out[2] = DotProduct(in1, in2[2]) + in2[2][3];
}

FORCEINLINE void VectorTransform( const Vector& in1, const matrix3x4_t &in2, Vector &out )
{
	VectorTransform( &in1.x, in2, &out.x );
}

void inline SinCos( float radians, float *sine, float *cosine )
{
#ifdef _WIN32
	_asm
	{
		fld		DWORD PTR [radians]
		fsincos

		mov edx, DWORD PTR [cosine]
		mov eax, DWORD PTR [sine]

		fstp DWORD PTR [edx]
		fstp DWORD PTR [eax]
	}
#elif _LINUX
	register double __cosr, __sinr;
 	__asm __volatile__
    		("fsincos"
     	: "=t" (__cosr), "=u" (__sinr) : "0" (radians));

  	*sine = __sinr;
  	*cosine = __cosr;
#endif
}

FORCEINLINE void AngleVectors( const QAngle &angles, Vector* forward)
{
	float sp, sy, cp, cy;
	
	SinCos( DEG2RAD( angles[1] ), &sy, &cy );
	SinCos( DEG2RAD( angles[0] ), &sp, &cp );

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

FORCEINLINE void AngleVectors( const QAngle &angles, Vector* forward, Vector* right, Vector* up )
{
	float sr, sp, sy, cr, cp, cy;
	
	SinCos( DEG2RAD( angles[1] ), &sy, &cy );
	SinCos( DEG2RAD( angles[0] ), &sp, &cp );
	SinCos( DEG2RAD( angles[2] ), &sr, &cr );

	if(forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if(right)
	{
		right->x = (-1*sr*sp*cy+-1*cr*-sy);
		right->y = (-1*sr*sp*sy+-1*cr*cy);
		right->z = -1*sr*cp;
	}

	if(up)
	{
		up->x = (cr*sp*cy+-sr*-sy);
		up->y = (cr*sp*sy+-sr*cy);
		up->z = cr*cp;
	}
}

FORCEINLINE void AngleVectorsTranspose (const QAngle &angles, Vector *forward, Vector *right, Vector *up)
{
	float sr, sp, sy, cr, cp, cy;
	
	SinCos( DEG2RAD( angles[1] ), &sy, &cy );
	SinCos( DEG2RAD( angles[0] ), &sp, &cp );
	SinCos( DEG2RAD( angles[2] ), &sr, &cr );

	if (forward)
	{
		forward->x	= cp*cy;
		forward->y	= (sr*sp*cy+cr*-sy);
		forward->z	= (cr*sp*cy+-sr*-sy);
	}
	
	if (right)
	{
		right->x	= cp*sy;
		right->y	= (sr*sp*sy+cr*cy);
		right->z	= (cr*sp*sy+-sr*cy);
	}

	if (up)
	{
		up->x		= -sp;
		up->y		= sr*cp;
		up->z		= cr*cp;
	}
}

FORCEINLINE void VectorAngles( const Vector& forward, QAngle &angles )
{
	double tmp, yaw, pitch;
	double fx = forward[0], fy = forward[1], fz = forward.z;
	if (fy == 0.0 && fx == 0.0)
	{
		yaw = 0.0;
		pitch = 0.0;
	}
	else
	{
		yaw = (atan2(fy, fx) * 180.0 / M_PI);
		if (yaw < 0.0)
			yaw += 360.0;

		tmp = sqrt (fx * fx + fy * fy);
		pitch = (atan2(-fz, tmp) * 180.0 / M_PI);
	}
	
	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

FORCEINLINE float fastskrrrt( float ehi )
{
	float tmp = ehi;
	float half = 0.5f * ehi;
	int i = *reinterpret_cast< int* >( &ehi );

	i = 0x5f3759df - ( i >> 1 );
	ehi = *reinterpret_cast<float*>( &i );
  
	ehi = ehi * ( 1.5f - half * ehi * ehi ); 
	ehi = ehi * ( 1.5f - half * ehi * ehi );

	return tmp * ehi;
}

FORCEINLINE void VectorToEulerAngles( const Vector& forward, QAngle &angles )
{
	float tmp, yaw, pitch;
	
	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = fastskrrrt(forward[0]*forward[0] + forward[1]*forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}
	
	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

#endif //__VECTOR_H__

