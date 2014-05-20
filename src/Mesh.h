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
struct Face {
	vector<int> vertexIndex;
	vector<int> normalIndex;
	int mtlIndex;
};

struct Material {
	string name;
	GLfloat Ka[3];
	GLfloat Kd[3];
	GLfloat Ks[3];
	GLfloat Ns;
};
class Mesh {
private:
	vector<string> mtlFile;
	string meshFile;
	vector<Vector3> vertices;
	vector<Vector3> normalVectors;
	vector<Face> faces;
	Vector3 rotatedAngle;
	void parseMaterial(string mtlName);
public:
	vector<Material> materials;
	vector<Mesh> componentMesh;
	float sumAngle;
	Vector3 center;
	float edgeLength;
	Mesh(Vector3, float);
	Mesh();
	void loadMtl(const char* mtlFile);
	bool getMesh(const char * fileName);
	void drawFace();
	void drawFaces();
	void rotateMesh(int xyz);
	void calculateRotateMesh(int xyz);
	void drawMesh();
	void computeCenter();
	void toString();
};

#endif /* MESH_H_ */
