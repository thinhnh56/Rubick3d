/*
 * Mesh.h
 *
 *  Created on: May 11, 2014
 *      Author: lament
 */

#ifndef MESH_H_
#define MESH_H_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#define MESH_FILE "blablabla.obj"

using namespace std;
struct Face{
	vector<int> vertexIndex;
	vector<int> normalIndex;
};
struct Vec3{
	float x, y, z;
};
struct Vec3i{
	int x, y, z;
};

class Mesh{
private:
	string meshFile;
	vector<Vec3> vertex;
	vector<Vec3> normalVec;
	vector<Face> face;
	
	Vec3i rotatedAngle = {0,0,0};
public:
	bool getMesh(const char * fileName);	
	void drawFace();
	
	void rotateMesh(float angle, int xyz);
	void drawMesh();
	
	void toString();
};




#endif /* MESH_H_ */
