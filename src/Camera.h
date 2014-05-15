//#pragma once
//#include "Point3.h"
//#include "Vector3.h"
//#include <cmath.h>
//class Camera
//{
//public:
//	Camera(); // default constructor
//	void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt
//	void roll(float angle); // roll it
//	void pitch(float angle); // increase pitch
//	void yaw(float angle); // yaw it
//	void slide(float delU, float delV, float delN); // slide it
//	void setShape(float vAng, float asp, float nearD, float farD);
//	void getShape(float &vAng, float &asp, float &nearD, float &farD);
//	void move(Vector3 v);
//	~Camera();
//
//private:
//	Point3 eye;
//	Vector3 u, v, n;
//	double viewAngle, aspect, nearDist, farDist; // view  volume shape
//	void setModelViewMatrix(); // tell OpenGL where the camera is
//};
//

#ifndef _HlCamera
#define _HlCamera
//#include "SDL.h" // needed for Vector3 definitions
#include "Vector3.h"
#include "Point3.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;
//##################### class CAMERA ######################
class Camera{
 private:
  Point3 eye;
  Vector3 u, v, n;
  float aspect, nearDist, farDist, viewAngle;
  void setModelViewMatrix();

 public:
  Camera(void);
  void roll(float angle);
  void pitch(float angle);
  void yaw(float angle);
  void slide(double du, double dv, double dn);
  void set(Point3 Eye, Point3 look, Vector3 up);
  void setShape(float viewAngle, float aspect, float Near, float Far);
  void setAspect(float asp);
  void getShape(float& viewAngle, float& aspect, float& Near, float& Far);
  void rotAxes(Vector3& a, Vector3& b, float angle);
  void setDefaultCamera();
  void getAxes(Vector3 &u, Vector3 &v, Vector3 &n);
  void setAxes(Vector3 &u, Vector3 &v, Vector3 &n);
  void printPosition();
};
#endif

