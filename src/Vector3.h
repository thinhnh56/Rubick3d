#pragma once
#include "Point3.h"
#include <iostream>
#include <cmath>
using namespace std;
/*
class Vector3
{
public:
	 3 coordinates of the vector (x, y, z)
	float x, y, z;
	 set function
	void set(const float dx, const float dy, const float dz);
	 set function
	void set(const Vector3 &v);
	 reverse this vector
	void flip();
	 set this vector = point a - point b
	void setDiff(const Point3& a, const Point3 &b);
	 adjust this vector to unit length
	void normalize();
	Vector3(const float xx, const float yy, const float zz);
	Vector3(const Vector3 &v);
	Vector3();
	//return this cross b
	Vector3 cross(const Vector3 &b);
	// return this dotted with b
	float dot(Vector3 b); 

	~Vector3();
};

*/
class Vector3{
 public:
  float x,y,z;

  Vector3(float xx, float yy, float zz){
	  x = xx; y = yy; z = zz;
  }
  /*Vector3(Vector3& v){
	  x = v.x; y = v.y; z = v.z;
  }*/
  Vector3(){
	  x = y = z = 0;
  } //default constructor

  Vector3 cross(Vector3 b); //return this cross b

  float dot(Vector3 b); // return this dotted with b
  void flip(){x = -x; y = -y; z = -z;} // reverse this vector
  void normalize();//adjust this vector to unit length
  void set(float dx, float dy, float dz){ x = dx; y = dy; z = dz;}
  void set(const Vector3& v){ x = v.x; y = v.y; z = v.z;}
  void setDiff(Point3& a, Point3& b)//set to difference a - b
    { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;}
};
