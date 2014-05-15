/*
#include "Vector3.h"

Vector3::Vector3() {
	set(0, 0, 0);
}
Vector3::Vector3(const float xx, const float yy, const float zz) {
	x = xx;
	y = yy;
	z = zz;
}
Vector3::Vector3(const Vector3 &v) {
	x = v.x;
	y = v.y;
	z = v.z;
}
 set function
void Vector3::set(const float dx, const float dy, const float dz) {
	x = dx;
	y = dy;
	z = dz;
}
 set function
void Vector3::set(const Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}
 reverse this vector
void Vector3::flip() {
	x = -x;
	y = -y;
	z = -z;
}
 set this vector = point a - point b
void Vector3::setDiff(const Point3& a, const Point3& b) {
	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
}
 adjust this vector to unit length
void Vector3::normalize() {

}

// return this dotted with b
float Vector3::dot(Vector3 b) {
	return x * b.x + y * b.y + z * b.z;
}

//return this cross b
Vector3 Vector3::cross(const Vector3 &b) {
	return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
}

Vector3::~Vector3() {
}
*/
#include "Vector3.h"
Vector3 Vector3 :: cross(Vector3 b) //return this cross b
{
  Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
  return c;
}
float Vector3 :: dot(Vector3 b) // return this dotted with b
{return x * b.x + y * b.y + z * b.z;}

void Vector3 :: normalize()//adjust this vector to unit length
{
  double sizeSq = x * x + y * y + z * z;
  if(sizeSq < 0.0000001)
    {
      cerr << "\nnormalize() sees vector (0,0,0)!";
      return; // does nothing to zero vectors;
    }
  float scaleFactor = 1.0/(float)sqrt(sizeSq);
  x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
}
