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
	Mesh* tempMesh;
	bool flag = false;
	while (1){
		int res = fscanf(file, "%s", header);

		if (this->componentMesh.size() != 0){
			tempMesh = &componentMesh[componentMesh.size() - 1];
		}
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
			tempMesh->vertex.push_back(tempVer);

		}
		if ( strcmp(header, "vn") == 0){
			Vec3 tempNorm;
			fscanf(file, " %f %f %f ", &tempNorm.x, &tempNorm.y, &tempNorm.z);
			tempMesh->normalVec.push_back(tempNorm);

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
			tempMesh->face.push_back(tempFace);
			if (tempMesh->normalVec.size() == 0){
				tempMesh->normalVec = componentMesh[componentMesh.size() - 2].normalVec;
				tempMesh->vertex = componentMesh[componentMesh.size() - 2].vertex;
			}
		}
		if (strcmp(header, "g") == 0){
			if (flag == false){
				Mesh  newMesh;
				componentMesh.push_back(newMesh);
				flag = true;
			}else{
				flag = false;
			}
		}
	}
	return true;
}
void Mesh::drawFace(){

	for (int m =0 ; m<componentMesh.size(); m++){
		//Mesh tempMesh;
		//tempMesh = componentMesh[m];
		for (int i=0; i<componentMesh[m].face.size(); ++i){
			glBegin(GL_POLYGON);
			for (int j=0; j<componentMesh[m].face[i].vertexIndex.size(); ++j ){
				Vec3 temp_normal = componentMesh[m].normalVec[componentMesh[m].face[i].normalIndex[j]];
				glNormal3f(temp_normal.x, temp_normal.y, temp_normal.z);
				Vec3 temp_ver = componentMesh[m].vertex[ componentMesh[m].face[i].vertexIndex[j] ];
				glVertex3f(temp_ver.x, temp_ver.y, temp_ver.z);
			}
			glEnd();
		}
		glFlush();
	}
}

void Mesh::toString(){
	for (int m =0; m<componentMesh.size(); m++){
		cout << "component " << m << endl;
		cout << "Mesh vertex" << endl;
		for (int i=0; i<componentMesh[m].vertex.size(); ++i){
			cout << componentMesh[m].vertex[i].x << " " << componentMesh[m].vertex[i].y << " " << componentMesh[m].vertex[i].z << endl;
		}
		cout << "Mesh normal"<< endl;
		for (int i=0; i<componentMesh[m].normalVec.size(); i++){
			cout << componentMesh[m].normalVec[i].x << " " << componentMesh[m].normalVec[i].y << " " << componentMesh[m].normalVec[i].z << endl;
		}
		cout << "Mesh Face" << endl;
		for (int i=0; i<componentMesh[m].face.size(); ++i){
			for (int j=0; j<componentMesh[m].face[i].normalIndex.size(); j++){
				cout << componentMesh[m].face[i].normalIndex[j] << "/" << componentMesh[m].face[i].vertexIndex[j] << " ";
			}
			cout << endl;
		}
	}
}







