#include "Camera.h"
#include <cmath>
#include <gl/glut.h>

float PI = 3.14159265;

Camera::Camera()
{
	aspect = -1;
	farDist = -1;
	viewAngle = -1;
	nearDist = -1;
}

void Camera::set(Point3 eye_, Point3 look, Vector3 up){
	eye.set(eye_); // store the given eye position
	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
	// make n
	u.set(up.cross(n));
	n.normalize();
	u.normalize();
	v.set(n.cross(u)); // make v = n X u
	setModelViewMatrix(); // tell OpenGL 
}
void Camera::roll(float angle){
	float cs = cos(PI / 180 * angle);
	//convert degrees to radians
	float sn = sin(PI / 180 * angle);
	Vector3 t(u); // remember old u
	u.set(cs*t.x - sn*v.x, cs*t.y - sn*v.y, cs*t.z - sn*v.z);
	v.set(sn*t.x + cs*v.x, sn*t.y + cs*v.y, sn*t.z + cs*v.z);
	setModelViewMatrix();
}
void Camera::pitch(float angle){

}
void Camera::yaw(float angle){

}
void Camera::slide(float delU, float delV, float delN){
	eye.x += delU * u.x + delV * v.x + delN * n.x;
	eye.y += delU * u.y + delV * v.y + delN * n.y;
	eye.z += delU * u.z + delV * v.z + delN * n.z;
	setModelViewMatrix();
}
void Camera::setShape(float vAng, float asp, float nearD, float farD){
	glMatrixMode(GL_PROJECTION);
	gluPerspective(vAng, asp, nearD, farD);
}
void Camera::getShape(float &vAng, float &asp, float &nearD, float &farD){

}
void Camera::move(Vector3 p){
	eye.set(eye.x + p.x, eye.y + p.y, eye.z + p.z);
	setModelViewMatrix();
}
Camera::~Camera()
{
}

void Camera::setModelViewMatrix(){
	float m[16];
	Vector3 eVec(eye.x, eye.y, eye.z); // a vector version of eye
	m[0] = u.x; m[4] = u.y; m[8] = u.z; m[12] = -eVec.dot(u);
	m[1] = v.x; m[5] = v.y; m[9] = v.z; m[13] = -eVec.dot(v);
	m[2] = n.x; m[6] = n.y; m[10] = n.z; m[14] = -eVec.dot(n);
	m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}
