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
const float RATE = 0.5;
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

bool Mesh::getMesh(const char * fileName, const char* mtlFile){
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
			tempVer = tempVer * RATE;
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
	for (int i=0; i<(int)componentMesh.size() - 1; i++){
		for (int j=0; j<(int)componentMesh[i].face.size(); j++){
			tempFaceVertex.clear();
			tempNormalVector.clear();
			for (int k = 0; k< (int)componentMesh[i].face[j].vertexIndex.size(); k++){
				Vector3 tempVer = componentMesh[i].vertex[componentMesh[i].face[j].vertexIndex[k]];
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

void Mesh::drawFaces()
{
     GLfloat faceVertex[9];
	 GLfloat normal[9];
	 vector<float> tempFaceVertex;
	 vector<float> tempNormalVector;

     for (int j=0; j<(int)face.size(); j++){


			tempFaceVertex.clear();
			tempNormalVector.clear();
			for (int k = 0; k<(int)face[j].vertexIndex.size(); k++){
				Vector3 tempVer = vertex[face[j].vertexIndex[k]];
				tempFaceVertex.push_back(tempVer.x);
				tempFaceVertex.push_back(tempVer.y);
				tempFaceVertex.push_back(tempVer.z);
				Vector3 tempNorm = normalVec[face[j].normalIndex[k]];
				tempNormalVector.push_back(tempNorm.x);
				tempNormalVector.push_back(tempNorm.y);
				tempNormalVector.push_back(tempNorm.z);
			}
			copy(tempFaceVertex.begin(), tempFaceVertex.end(), faceVertex );
			copy(tempNormalVector.begin(), tempNormalVector.end(), normal);

			if (face[j].mtlIndex == 25)
				glColor3f(1, 1, 1);
			if (face[j].mtlIndex == 26)
				glColor3f(1, 0, 0);
			if (face[j].mtlIndex == 27)
				glColor3f(0, 1, 0);
			if (face[j].mtlIndex == 28)
				glColor3f(0, 0, 1);
			if (face[j].mtlIndex == 29)
				glColor3f(1, 1, 0);
			if (face[j].mtlIndex == 30)
				glColor3f(0, 1, 1);
			if (face[j].mtlIndex == 31)
				glColor3f(1, 0, 1);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, faceVertex);
			glNormalPointer(GL_FLOAT, 0,normal);

			glDrawArrays(GL_TRIANGLES, 0, 9);
			glDisableClientState(GL_VERTEX_ARRAY);

		}
}

void Mesh::toString(){
	for (int m =13; m<(int)/*componentMesh.size()*/14; m++){
		cout << "component " << m << endl;
		cout << "Mesh vertex" << endl;
		for (int i=0; i<(int)componentMesh[m].vertex.size(); ++i){
			cout << componentMesh[m].vertex[i].x << " " << componentMesh[m].vertex[i].y << " " << componentMesh[m].vertex[i].z << endl;
		}
		cout << "Mesh normal"<< endl;
		for (int i=0; i<(int)componentMesh[m].normalVec.size(); i++){
			cout << componentMesh[m].normalVec[i].x << " " << componentMesh[m].normalVec[i].y << " " << componentMesh[m].normalVec[i].z << endl;
		}
		cout << "Mesh Face" << endl;
		for (int i=0; i<(int)componentMesh[m].face.size(); ++i){
			cout << "mtl" << componentMesh[m].face[i].mtlIndex << " ";
			for (int j=0; j<(int)componentMesh[m].face[i].normalIndex.size(); j++){
				cout << componentMesh[m].face[i].normalIndex[j] << "/" << componentMesh[m].face[i].vertexIndex[j] << " ";
			}
			cout << endl;
		}
	}

	for (int i=0; i<100; i++){
		cout << endl << "material " << i << endl;
		cout << materials[i].Ka[0] << " ";
		cout << materials[i].Ka[1] << " ";
		cout << materials[i].Ka[2] << " ";
		cout << endl;
		cout << materials[i].Kd[0] << " ";
		cout << materials[i].Kd[1] << " ";
		cout << materials[i].Kd[2] << " ";
		cout << endl;
		cout << materials[i].Ks[0] << " ";
		cout << materials[i].Ks[1] << " ";
		cout << materials[i].Ks[2] << " ";
	}
}


Mesh::Mesh( Vector3 v, float l)
{
            center = Vector3(v);
            edgeLength = l;
            rotatedAngle = Vector3(0,0,0);
            sumAngle = 0;
}
Mesh::Mesh()
{
            edgeLength = INITLENGTH * RATE;
            rotatedAngle = Vector3(0,0,0);
            sumAngle = 0;
}

void Mesh:: rotateMesh(int xyz)
{
     if(xyz == 1)
     {
            this->rotatedAngle.x += addAngle;
     }       
     if(xyz == 2)
     {
            this->rotatedAngle.y += addAngle;
     }
     if(xyz == 3)
     {
            this->rotatedAngle.z += addAngle;
     }
}

void Mesh:: calculateRotateMesh(int xyz)
{
     
     if(xyz == 1)
     {
            for(int i = 0;i<(int)vertex.size();i++)
                    vertex[i] = Vector3(vertex[i].x,-vertex[i].z,vertex[i].y);
            for(int i = 0;i<(int)this->normalVec.size();i++)
                    normalVec[i] = Vector3(normalVec[i].x,-normalVec[i].z,normalVec[i].y);
            center = Vector3(center.x,-center.z,center.y);
     }       
     if(xyz == 2)
     {
            for(int i = 0;i<(int)vertex.size();i++)
                    vertex[i] = Vector3(vertex[i].z,vertex[i].y,-vertex[i].x);
            for(int i = 0;i<(int)this->normalVec.size();i++)
                    normalVec[i] = Vector3(normalVec[i].z,normalVec[i].y,-normalVec[i].x);
            center = Vector3(center.z,center.y,-center.x);
     }
     if(xyz == 3)
     {
            for(int i = 0;i<(int)vertex.size();i++)
                    vertex[i] = Vector3(-vertex[i].y,vertex[i].x,vertex[i].z);
            for(int i = 0;i<(int)this->normalVec.size();i++)
                    normalVec[i] = Vector3(-normalVec[i].y,normalVec[i].x,normalVec[i].z);
            center = Vector3(-center.y,center.x,center.z);
     }
}

void Mesh:: drawMesh()
{
     sumAngle = this->rotatedAngle.x + this->rotatedAngle.y  + this->rotatedAngle.z;
     if( sumAngle > 90)
     {
         if(this->rotatedAngle.x > 0) calculateRotateMesh(1);
         if(this->rotatedAngle.y > 0) calculateRotateMesh(2);
         if(this->rotatedAngle.z > 0) calculateRotateMesh(3);
         this->rotatedAngle.x = 0;
         this->rotatedAngle.y = 0;
         this->rotatedAngle.z = 0;
     }
     if( sumAngle > 0)
     {
     glPushMatrix();  
     
     glRotated(this->rotatedAngle.x,1,0,0);
     glRotated(this->rotatedAngle.y,0,1,0);
     glRotated(this->rotatedAngle.z,0,0,1);
     
     if( this->rotatedAngle.x > 0)
         this->rotatedAngle.x += addAngle;
     if( this->rotatedAngle.y > 0)
         this->rotatedAngle.y += addAngle;
     if( this->rotatedAngle.z > 0)
         this->rotatedAngle.z += addAngle;                        
     this->drawFaces();
	 glPopMatrix();
    }
    else drawFaces();
}
void Mesh::computeCenter()
{
     float amx = 0, duongx = 0;
     float amy = 0, duongy = 0;
     float amz = 0, duongz = 0;
     for(int i = 0;i<(int)vertex.size();i++)
     {
             if(amx*duongx ==0){
             if(vertex[i].x < 0) amx = -1;
             if(vertex[i].x > 0) duongx = 1;
             }
             if(amy*duongy ==0){
             if(vertex[i].y < 0) amy = -1;
             if(vertex[i].y > 0) duongy = 1;
             }
             if(amz*duongz ==0){
             if(vertex[i].z < 0) amz = -1;
             if(vertex[i].z > 0) duongz = 1;
             }
     }
     
     center = Vector3(edgeLength*(amx+duongx), edgeLength*(amy+duongy), edgeLength*(amz+duongz));
     
}

