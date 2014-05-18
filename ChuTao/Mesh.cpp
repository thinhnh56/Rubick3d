/*
 * Mesh.cpp
 *
 *  Created on: May 11, 2014
 *      Author: lament
 */
#include "Mesh.h"

const int addAngle = 10;

bool Mesh::getMesh(const char * fileName) {
	FILE * file = fopen(fileName, "r");
	if (file == NULL) {
		cout << "error reading file " << fileName << endl;
		return false;
	}
	char header[256];
	while (1) {
		int res = fscanf(file, "%s", header);
		//cout << header << endl;
		if (res == EOF) {
			break;
		}
		if (strcmp(header, "v") == 0) {
			Vec3 tempVer;
			tempVer.x = 0;
			tempVer.y = 0;
			tempVer.z = 0;
			fscanf(file, " %f %f %f ", &tempVer.x, &tempVer.y, &tempVer.z);
			//cout << tempVer.x << tempVer.y << tempVer.z << endl;
			this->vertex.push_back(tempVer);
		}
		if (strcmp(header, "vn") == 0) {
			Vec3 tempNorm;
			fscanf(file, " %f %f %f ", &tempNorm.x, &tempNorm.y, &tempNorm.z);
			this->normalVec.push_back(tempNorm);
		}
		if (strcmp(header, "f") == 0) {
			Face tempFace;
			int tempVer, tempNorm;

			fscanf(file, "%d//%d ", &tempVer, &tempNorm);
			tempFace.normalIndex.push_back(tempNorm - 1);
			tempFace.vertexIndex.push_back(tempVer - 1);

			fscanf(file, "%d//%d", &tempVer, &tempNorm);
			tempFace.normalIndex.push_back(tempNorm - 1);
			tempFace.vertexIndex.push_back(tempVer - 1);

			fscanf(file, "%d//%d", &tempVer, &tempNorm);
			tempFace.normalIndex.push_back(tempNorm - 1);
			tempFace.vertexIndex.push_back(tempVer - 1);

			this->face.push_back(tempFace);
		}
	}
	return true;
}
void Mesh::drawFace() {
	for (int i = 0; i < (int) this->face.size(); ++i) {
		glBegin(GL_POLYGON);
		for (int j = 0; j <(int)  this->face[i].vertexIndex.size(); ++j) {
			Vec3 temp_normal = this->normalVec[this->face[i].normalIndex[j]];
			glNormal3f(temp_normal.x, temp_normal.y, temp_normal.z);
			Vec3 temp_ver = this->vertex[this->face[i].vertexIndex[j]];
			glVertex3f(temp_ver.x, temp_ver.y, temp_ver.z);
		}
		glEnd();
	}
	glFlush();
}

void Mesh::toString() {
	cout << "Mesh vertex" << endl;
	for (int i = 0; i <(int)  this->vertex.size(); ++i) {
		cout << this->vertex[i].x << " " << this->vertex[i].y << " "
				<< this->vertex[i].z << endl;
	}
	cout << "Mesh normal" << endl;
	for (int i = 0; i <(int)  this->normalVec.size(); i++) {
		cout << this->normalVec[i].x << " " << this->normalVec[i].y << " "
				<< this->normalVec[i].z << endl;
	}
	cout << "Mesh Face" << endl;
	for (int i = 0; i < (int) this->face.size(); ++i) {
		for (int j = 0; j < (int) this->face[i].normalIndex.size(); j++) {
			cout << this->face[i].normalIndex[j] << "/"
					<< this->face[i].vertexIndex[j] << " ";
		}
		cout << endl;
	}
}

void Mesh:: rotateMesh(int xyz)
{
     if(xyz == 1)
            this->rotatedAngle.x += addAngle;
     if(xyz == 2)
            this->rotatedAngle.y += addAngle;
     if(xyz == 3)
            this->rotatedAngle.z += addAngle;
}

void Mesh:: drawMesh()
{
     glPushMatrix();  
     glRotated(this->rotatedAngle.x,1,0,0);
     glRotated(this->rotatedAngle.y,0,1,0);
     glRotated(this->rotatedAngle.z,0,0,1);
     if( this->rotatedAngle.x %90 > 0)
         this->rotatedAngle.x += addAngle;
     if( this->rotatedAngle.y %90 > 0)
         this->rotatedAngle.y += addAngle;
     if( this->rotatedAngle.z %90 > 0)
         this->rotatedAngle.z += addAngle;                        
     this->drawFace();
	 glPopMatrix();
	 
}
