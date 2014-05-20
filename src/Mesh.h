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
#include "Vector3.h"
#define MESH_FILE "blablabla.obj"

using namespace std;
struct Face{
	vector<int> vertexIndex;
	vector<int> normalIndex;
	int mtlIndex;
};

struct Material{
	string name;
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Ns;
};
class Mesh{
private:
	string meshFile;
	Material materials[100];
	vector<Vector3> vertex;
	vector<Vector3> normalVec;
	vector<Face> face;
	Vector3 rotatedAngle;
	
public:
       vector<Mesh> componentMesh;
       float sumAngle;
       Vector3 center;
       float edgeLength;
       Mesh(Vector3 ,float);
       Mesh();
       void loadMtl(const char* mtlFile);
	   bool getMesh(const char * fileName, const char*);
	   void drawFace();
	   void drawFaces();
	   void rotateMesh(int xyz);
	   void calculateRotateMesh(int xyz);
	   void drawMesh();
	   void computeCenter();
	   void toString();
};


#endif /* MESH_H_ */
