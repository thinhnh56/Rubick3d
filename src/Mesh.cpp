/*
 * Mesh.cpp
 *
 *  Created on: May 11, 2014
 *      Author: lament
 */
#include "Mesh.h"

bool Mesh::getMesh(const char * fileName){
	FILE * file = fopen(fileName, "r");
	if (file == NULL){
		cout << "error reading file " << fileName << endl;
		return false;
	}
	char header[256];
	while (1){
		int res = fscanf(file, "%s", header);
		//cout << header << endl;
		if (res == EOF){
			break;
		}
		if ( strcmp( header, "v") == 0){
			Vec3 tempVer;
			tempVer.x = 0;
			tempVer.y = 0;
			tempVer.z = 0;
			fscanf(file, " %f %f %f ", &tempVer.x, &tempVer.y, &tempVer.z);
			//cout << tempVer.x << tempVer.y << tempVer.z << endl;
			this->vertex.push_back(tempVer);
		}
		if ( strcmp(header, "vn") == 0){
			Vec3 tempNorm;
			fscanf(file, " %f %f %f ", &tempNorm.x, &tempNorm.y, &tempNorm.z);
			this->normalVec.push_back(tempNorm);
		}
		if ( strcmp(header, "f")  == 0){
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
void Mesh::drawFace(){
	for (int i=0; i<this->face.size(); ++i){
		glBegin(GL_POLYGON);
		for (int j=0; j<this->face[i].vertexIndex.size(); ++j ){
			Vec3 temp_normal = this->normalVec[this->face[i].normalIndex[j]];
			glNormal3f(temp_normal.x, temp_normal.y, temp_normal.z);
			Vec3 temp_ver = this->vertex[ this->face[i].vertexIndex[j] ];
			glVertex3f(temp_ver.x, temp_ver.y, temp_ver.z);
		}
		glEnd();
	}
	glFlush();
}

void Mesh::toString(){
	cout << "Mesh vertex" << endl;
	for (int i=0; i<this->vertex.size(); ++i){
		cout << this->vertex[i].x << " " << this->vertex[i].y << " " << this->vertex[i].z << endl;
	}
	cout << "Mesh normal"<< endl;
	for (int i=0; i<this->normalVec.size(); i++){
		cout << this->normalVec[i].x << " " << this->normalVec[i].y << " " << this->normalVec[i].z << endl;
	}
	cout << "Mesh Face" << endl;
	for (int i=0; i<this->face.size(); ++i){
		for (int j=0; j<this->face[i].normalIndex.size(); j++){
			cout << this->face[i].normalIndex[j] << "/" << this->face[i].vertexIndex[j] << " ";
		}
		cout << endl;
	}
}







