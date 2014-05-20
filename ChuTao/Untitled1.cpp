/*
 * Mesh.cpp
 *
 *  Created on: May 11, 2014
 *      Author: lament
 */
#include "Mesh.h"
void Mesh::loadMtl(const char* mtlFile){
	FILE* file = fopen(mtlFile, "r");
	if (file == NULL){
		cout << "error reading mtl file" ;
		return;
	}
	char header[256];
	int mtlIndex;
	while(1){
		int res = fscanf(file, "%s", header);
		if (res == EOF){
			break;
		}
		if (strcmp(header, "newmtl") == 0){
			fscanf(file, " %d", &mtlIndex);
			//cout << mtlIndex<< endl;
			float x, y, z;
			res = fscanf(file, "%s", header);
			if (strcmp(header, "Ka") == 0){
				fscanf(file, "  %f %f %f", &materials[mtlIndex].Ka[0], &materials[mtlIndex].Ka[1], &materials[mtlIndex].Ka[2]);

			}
			res = fscanf(file, "%s", header);
			if (strcmp(header, "Kd") == 0){
				fscanf(file, "  %f %f %f", &materials[mtlIndex].Kd[0], &materials[mtlIndex].Kd[1], &materials[mtlIndex].Kd[2]);
			}
			res = fscanf(file, "%s", header);
			if (strcmp(header, "Ks") == 0){
				fscanf(file, "  %f %f %f", &materials[mtlIndex].Ks[0], &materials[mtlIndex].Ks[1], &materials[mtlIndex].Ks[2]);
			}
			materials[mtlIndex].Ns = 0;
		}
	}
}
bool Mesh::getMesh(const char * fileName){
	FILE * file = fopen(fileName, "r");
	if (file == NULL){
		cout << "error reading file " << fileName << endl;
		return false;
	}
	char header[256];
	Mesh* tempMesh;
	bool flag = false;
	int currentMtlIndex = 0;
	loadMtl(mtlFile);
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
			Vector3 tempVer;
			tempVer.x = 0;
			tempVer.y = 0;
			tempVer.z = 0;
			fscanf(file, " %f %f %f ", &tempVer.x, &tempVer.y, &tempVer.z);
			//cout << tempVer.x << tempVer.y << tempVer.z << endl;
			tempMesh->vertex.push_back(tempVer);

		}
		if ( strcmp(header, "vn") == 0){
			Vector3 tempNorm;
			fscanf(file, " %f %f %f ", &tempNorm.x, &tempNorm.y, &tempNorm.z);
			tempMesh->normalVec.push_back(tempNorm);

		}
		if (strcmp(header, "usemtl") == 0){
			fscanf(file, " %d", &currentMtlIndex);
			//cout << currentMtlIndex << endl;
		}
		if ( strcmp(header, "f")  == 0){
			Face tempFace;
			int tempVer, tempNorm;

			tempFace.mtlIndex = currentMtlIndex;

			fscanf(file, "%d//%d ", &tempVer, &tempNorm);
			if (componentMesh.size() < 2){
				tempFace.normalIndex.push_back(tempNorm - 1);
				tempFace.vertexIndex.push_back(tempVer - 1);
			}else{
				tempFace.normalIndex.push_back(tempNorm - 104*(componentMesh.size()-1) -1);
				tempFace.vertexIndex.push_back(tempVer - 104*(componentMesh.size()-1) -1);
			}
			fscanf(file, "%d//%d", &tempVer, &tempNorm);
			if (componentMesh.size() < 2){
				tempFace.normalIndex.push_back(tempNorm - 1);
				tempFace.vertexIndex.push_back(tempVer - 1);
			}else{
				tempFace.normalIndex.push_back(tempNorm - 104*(componentMesh.size()-1) -1);
				tempFace.vertexIndex.push_back(tempVer - 104*(componentMesh.size()-1) -1);
			}

			fscanf(file, "%d//%d", &tempVer, &tempNorm);
			if (componentMesh.size() < 2){
				tempFace.normalIndex.push_back(tempNorm - 1);
				tempFace.vertexIndex.push_back(tempVer - 1);
			}else{
				tempFace.normalIndex.push_back(tempNorm - 104*(componentMesh.size()-1) -1);
				tempFace.vertexIndex.push_back(tempVer - 104*(componentMesh.size()-1) -1);
			}
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

	float faceVertex[9];
	float normal[9];
	vector<float> tempFaceVertex;
	vector<float> tempNormalVector;
	for (int i=0; i<componentMesh.size() - 1; i++){
		for (int j=0; j<componentMesh[i].face.size(); j++){
			glMaterialfv(GL_FRONT, GL_SPECULAR, materials[componentMesh[i].face[j].mtlIndex].Ks);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[componentMesh[i].face[j].mtlIndex].Kd);
			glMaterialfv(GL_FRONT, GL_AMBIENT, materials[componentMesh[i].face[j].mtlIndex].Ka);
			glMaterialf(GL_FRONT, GL_SHININESS, materials[componentMesh[i].face[j].mtlIndex].Ns);

			tempFaceVertex.clear();
			tempNormalVector.clear();
			for (int k = 0; k<componentMesh[i].face[j].vertexIndex.size(); k++){
				Vector3 tempVer = componentMesh[i].vertex[componentMesh[i].face[j].vertexIndex[k]];
				tempFaceVertex.push_back(tempVer.x);
				tempFaceVertex.push_back(tempVer.y);
				tempFaceVertex.push_back(tempVer.z);
				Vector3 tempNorm = componentMesh[i].normalVec[componentMesh[i].face[j].normalIndex[k]];
				tempNormalVector.push_back(tempNorm.x);
				tempNormalVector.push_back(tempNorm.y);
				tempNormalVector.push_back(tempNorm.z);
			}
			copy(tempFaceVertex.begin(), tempFaceVertex.end(), faceVertex );
			copy(tempNormalVector.begin(), tempNormalVector.end(), normal);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, faceVertex);
			glNormalPointer(GL_FLOAT, 0,normal);
			glDrawArrays(GL_TRIANGLES, 0, 9);
			glDisableClientState(GL_VERTEX_ARRAY);
		}
	}
	glFlush();
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
			cout << "materials " << componentMesh[m].face[i].mtlIndex << "  ";
			for (int j=0; j<componentMesh[m].face[i].normalIndex.size(); j++){
				cout << componentMesh[m].face[i].normalIndex[j] << "/" << componentMesh[m].face[i].vertexIndex[j] << " ";
			}
			cout << endl;
		}
	}
}
