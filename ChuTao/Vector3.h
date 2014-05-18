#pragma once
#include "Point3.h"
#include <math.h>
class Vector3
{
public:
	/* 3 coordinates of the vector (x, y, z) */
	float x, y, z;
	/* set function */
	void set(const float dx, const float dy, const float dz);
	/* set function */
	void set(const Vector3 &v);
	/* reverse this vector */
	void flip();
	/* set this vector = point a - point b*/
	void setDiff(const Point3& a, const Point3 &b);
	/* adjust this vector to unit length */
	void normalize();
	Vector3(const float xx, const float yy, const float zz);
	Vector3(const Vector3 &v);
	Vector3();
	//return this cross b
	Vector3 cross(const Vector3 &b);
	// return this dotted with b
	
	float Distance(Vector3 b);
	Vector3 operator+(Vector3 b); 
	Vector3 operator-(Vector3 b); 
    Vector3 operator*(double k);
    Vector3 operator/(double k);
    float operator*(Vector3 b);
    
	~Vector3();
};

