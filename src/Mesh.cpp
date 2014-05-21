/*
 * Mesh.cpp
 *
 *  Created on: May 11, 2014
 *      Author: lament
 */
#include "Mesh.h"

const int addAngle = 10;
const float PI = 3.14159265;
const float INITLENGTH = 35.3428;
const float RATE = 1.25;

void Mesh::loadMtl(const char* mtlFile) {
	FILE* file = fopen(mtlFile, "r");
	if (file == NULL) {
		cout << "error reading mtl file";
		return;
	}
	char header[256];
	int mtlIndex;
	while (1) {
		int res = fscanf(file, "%s", header);
		if (res == EOF) {
			break;
		}
		if (strcmp(header, "newmtl") == 0) {
			Material m;
			fscanf(file, " %d", &mtlIndex);

			res = fscanf(file, "%s", header);
			if (strcmp(header, "Ka") == 0) {
				fscanf(file, "  %f %f %f", &m.Ka[0], &m.Ka[1], &m.Ka[2]);
			}
			res = fscanf(file, "%s", header);
			if (strcmp(header, "Kd") == 0) {
				fscanf(file, "  %f %f %f", &m.Kd[0], &m.Kd[1], &m.Kd[2]);
			}
			res = fscanf(file, "%s", header);
			if (strcmp(header, "Ks") == 0) {
				fscanf(file, "  %f %f %f", &m.Ks[0], &m.Ks[1], &m.Ks[2]);
			}
			res = fscanf(file, "%s", header);
			if (strcmp(header, "Ns") == 0) {
				fscanf(file, "  %f", &m.Ns);
			}
			materials.push_back(m);
		}
	}
}

bool Mesh::getMesh(const char * fileName) {
	FILE * file = fopen(fileName, "r");
	if (file == NULL) {
		cout << "error reading file " << fileName << endl;
		return false;
	}
	char header[256];
	Mesh* tempMesh;
	bool flag = false;
	int currentMtlIndex = 0;
	while (1) {
		int res = fscanf(file, "%s", header);

		if (this->componentMesh.size() != 0) {
			tempMesh = &componentMesh[componentMesh.size() - 1];
		}
		if (res == EOF) {
			break;
		}

		if (strcmp(header, "v") == 0) {
			Vector3 tempVer;
			tempVer.x = 0;
			tempVer.y = 0;
			tempVer.z = 0;
			fscanf(file, " %f %f %f ", &tempVer.x, &tempVer.y, &tempVer.z);
			tempVer = tempVer * RATE;
			tempMesh->vertices.push_back(tempVer);
			continue;
		}
		if (strcmp(header, "vn") == 0) {
			Vector3 tempNorm;
			fscanf(file, " %f %f %f ", &tempNorm.x, &tempNorm.y, &tempNorm.z);
			tempMesh->normals.push_back(tempNorm);
		}
		if (strcmp(header, "usemtl") == 0) {
			fscanf(file, " %d", &currentMtlIndex);
		}
		if (strcmp(header, "f") == 0) {
			Face tempFace;
			int tempVer, tempNorm;

			tempFace.mtlIndex = currentMtlIndex;

			fscanf(file, "%d//%d ", &tempVer, &tempNorm);
			if (componentMesh.size() < 2) {
				tempFace.normalIndex.push_back(tempNorm - 1);
				tempFace.vertexIndex.push_back(tempVer - 1);
			} else {
				tempFace.normalIndex.push_back(
						tempNorm - 104 * (componentMesh.size() - 1) - 1);
				tempFace.vertexIndex.push_back(
						tempVer - 104 * (componentMesh.size() - 1) - 1);
			}
			fscanf(file, "%d//%d", &tempVer, &tempNorm);
			if (componentMesh.size() < 2) {
				tempFace.normalIndex.push_back(tempNorm - 1);
				tempFace.vertexIndex.push_back(tempVer - 1);
			} else {
				tempFace.normalIndex.push_back(
						tempNorm - 104 * (componentMesh.size() - 1) - 1);
				tempFace.vertexIndex.push_back(
						tempVer - 104 * (componentMesh.size() - 1) - 1);
			}

			fscanf(file, "%d//%d", &tempVer, &tempNorm);
			if (componentMesh.size() < 2) {
				tempFace.normalIndex.push_back(tempNorm - 1);
				tempFace.vertexIndex.push_back(tempVer - 1);
			} else {
				tempFace.normalIndex.push_back(
						tempNorm - 104 * (componentMesh.size() - 1) - 1);
				tempFace.vertexIndex.push_back(
						tempVer - 104 * (componentMesh.size() - 1) - 1);
			}
			tempMesh->faces.push_back(tempFace);
			if (tempMesh->normals.size() == 0) {
				tempMesh->normals =
						componentMesh[componentMesh.size() - 2].normals;
				tempMesh->vertices =
						componentMesh[componentMesh.size() - 2].vertices;
			}
		}
		if (strcmp(header, "g") == 0) {
			if (flag == false) {
				Mesh newMesh;
				componentMesh.push_back(newMesh);
				flag = true;
			} else {
				flag = false;
			}
		}
	}
	return true;
}

void Mesh::drawFaces() {
	GLfloat faceVertex[9];
	GLfloat normal[9];
	vector<float> tempFaceVertex;
	vector<float> tempNormalVector;
	for (int j = 0; j < (int) faces.size(); j++) {
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_COLOR_MATERIAL_FACE);
		glMaterialfv(GL_FRONT, GL_SPECULAR,
				materials[faces[j].mtlIndex].Ks);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,
				materials[faces[j].mtlIndex].Kd);
		glMaterialfv(GL_FRONT, GL_AMBIENT,
				materials[faces[j].mtlIndex].Ka);
		glMaterialf(GL_FRONT, GL_SHININESS,
				materials[faces[j].mtlIndex].Ns);

//		GLfloat mat_specular[] = {0.3, 0.3, 1, 1.0};
//		GLfloat mat_shininess[] = { 10.0 };
//		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//		glEnable(GL_COLOR_MATERIAL);

		tempFaceVertex.clear();
		tempNormalVector.clear();
		for (int k = 0; k < (int) faces[j].vertexIndex.size(); k++) {
			Vector3 tempVer = vertices[faces[j].vertexIndex[k]];
			tempFaceVertex.push_back(tempVer.x);
			tempFaceVertex.push_back(tempVer.y);
			tempFaceVertex.push_back(tempVer.z);
			Vector3 tempNorm = normals[faces[j].normalIndex[k]];
			tempNormalVector.push_back(tempNorm.x);
			tempNormalVector.push_back(tempNorm.y);
			tempNormalVector.push_back(tempNorm.z);
		}
		copy(tempFaceVertex.begin(), tempFaceVertex.end(), faceVertex);
		copy(tempNormalVector.begin(), tempNormalVector.end(), normal);

//		if (faces[j].mtlIndex == 0)
//			glColor3f(1, 1, 1);
//		if (faces[j].mtlIndex == 1)
//			glColor3f(1, 0, 0);
//		if (faces[j].mtlIndex == 2)
//			glColor3f(0, 1, 0);
//		if (faces[j].mtlIndex == 3)
//			glColor3f(0, 0, 1);
//		if (faces[j].mtlIndex == 4)
//			glColor3f(1, 1, 0);
//		if (faces[j].mtlIndex == 5)
//			glColor3f(0, 1, 1);
//		if (faces[j].mtlIndex == 6)
//			glColor3f(1, 0, 1);
//		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_COLOR_MATERIAL);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, faceVertex);
		glNormalPointer(GL_FLOAT, 0, normal);

		glDrawArrays(GL_TRIANGLES, 0, 9);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Mesh::toString() {
	for (int m = 13; m < (int) 14; m++) {
		cout << "component " << m << endl;
		cout << "Mesh vertex" << endl;
		for (int i = 0; i < (int) componentMesh[m].vertices.size(); ++i) {
			cout << componentMesh[m].vertices[i].x << " "
					<< componentMesh[m].vertices[i].y << " "
					<< componentMesh[m].vertices[i].z << endl;
		}
		cout << "Mesh normal" << endl;
		for (int i = 0; i < (int) componentMesh[m].normals.size(); i++) {
			cout << componentMesh[m].normals[i].x << " "
					<< componentMesh[m].normals[i].y << " "
					<< componentMesh[m].normals[i].z << endl;
		}
		cout << "Mesh Face" << endl;
		for (int i = 0; i < (int) componentMesh[m].faces.size(); ++i) {
			cout << "mtl" << componentMesh[m].faces[i].mtlIndex << " ";
			for (int j = 0;
					j < (int) componentMesh[m].faces[i].normalIndex.size();
					j++) {
				cout << componentMesh[m].faces[i].normalIndex[j] << "/"
						<< componentMesh[m].faces[i].vertexIndex[j] << " ";
			}
			cout << endl;
		}
	}
}

Mesh::Mesh(Vector3 v, float l) {
	center = Vector3(v);
	edgeLength = l;
	rotatedAngle = Vector3(0, 0, 0);
	sumAngle = 0;
}
Mesh::Mesh() {
	edgeLength = INITLENGTH * RATE;
	rotatedAngle = Vector3(0, 0, 0);
	sumAngle = 0;
}

void Mesh::rotateMesh(int xyz) {
	if (xyz == 1) {
		this->rotatedAngle.x += addAngle;
	}
	if (xyz == 2) {
		this->rotatedAngle.y += addAngle;
	}
	if (xyz == 3) {
		this->rotatedAngle.z += addAngle;
	}
}

void Mesh::calculateRotateMesh(int xyz) {

	if (xyz == 1) {
		for (int i = 0; i < (int) vertices.size(); i++)
			vertices[i] = Vector3(vertices[i].x, -vertices[i].z, vertices[i].y);
		for (int i = 0; i < (int) this->normals.size(); i++)
			normals[i] = Vector3(normals[i].x, -normals[i].z, normals[i].y);
		center = Vector3(center.x, -center.z, center.y);
	}
	if (xyz == 2) {
		for (int i = 0; i < (int) vertices.size(); i++)
			vertices[i] = Vector3(vertices[i].z, vertices[i].y, -vertices[i].x);
		for (int i = 0; i < (int) this->normals.size(); i++)
			normals[i] = Vector3(normals[i].z, normals[i].y, -normals[i].x);
		center = Vector3(center.z, center.y, -center.x);
	}
	if (xyz == 3) {
		for (int i = 0; i < (int) vertices.size(); i++)
			vertices[i] = Vector3(-vertices[i].y, vertices[i].x, vertices[i].z);
		for (int i = 0; i < (int) this->normals.size(); i++)
			normals[i] = Vector3(-normals[i].y, normals[i].x, normals[i].z);
		center = Vector3(-center.y, center.x, center.z);
	}
}

void Mesh::drawMesh() {
	sumAngle = this->rotatedAngle.x + this->rotatedAngle.y
			+ this->rotatedAngle.z;
	if (sumAngle > 90) {
		if (this->rotatedAngle.x > 0)
			calculateRotateMesh(1);
		if (this->rotatedAngle.y > 0)
			calculateRotateMesh(2);
		if (this->rotatedAngle.z > 0)
			calculateRotateMesh(3);
		this->rotatedAngle.x = 0;
		this->rotatedAngle.y = 0;
		this->rotatedAngle.z = 0;
	}
	if (sumAngle > 0) {
		glPushMatrix();

		glRotated(this->rotatedAngle.x, 1, 0, 0);
		glRotated(this->rotatedAngle.y, 0, 1, 0);
		glRotated(this->rotatedAngle.z, 0, 0, 1);

		if (this->rotatedAngle.x > 0)
			this->rotatedAngle.x += addAngle;
		if (this->rotatedAngle.y > 0)
			this->rotatedAngle.y += addAngle;
		if (this->rotatedAngle.z > 0)
			this->rotatedAngle.z += addAngle;
		this->drawFaces();
		glPopMatrix();
	} else
		drawFaces();
}
void Mesh::computeCenter() {
	float amx = 0, duongx = 0;
	float amy = 0, duongy = 0;
	float amz = 0, duongz = 0;
	for (int i = 0; i < (int) vertices.size(); i++) {
		if (amx * duongx == 0) {
			if (vertices[i].x < 0)
				amx = -1;
			if (vertices[i].x > 0)
				duongx = 1;
		}
		if (amy * duongy == 0) {
			if (vertices[i].y < 0)
				amy = -1;
			if (vertices[i].y > 0)
				duongy = 1;
		}
		if (amz * duongz == 0) {
			if (vertices[i].z < 0)
				amz = -1;
			if (vertices[i].z > 0)
				duongz = 1;
		}
	}

	center = Vector3(edgeLength * (amx + duongx), edgeLength * (amy + duongy),
			edgeLength * (amz + duongz));

}

