#pragma once
#include "Point3.h"
#include "Vector3.h"
class Camera
{
public:
	Camera(); // default constructor
	void set(Point3 eye, Point3 look, Vector3 up); // like gluLookAt
	void roll(float angle); // roll it
	void pitch(float angle); // increase pitch
	void yaw(float angle); // yaw it
	void slide(float delU, float delV, float delN); // slide it
	void setShape(float vAng, float asp, float nearD, float farD);
	void getShape(float &vAng, float &asp, float &nearD, float &farD);
	void move(Vector3 v);
	~Camera();

private:
	Point3 eye;
	Vector3 u, v, n;
	double viewAngle, aspect, nearDist, farDist; // view  volume shape
	void setModelViewMatrix(); // tell OpenGL where the camera is
};

