/*
 * Mesh.cpp
 *
 *  Created on: May 11, 2014
 *      Author: lament
 */
#include "Mesh.h"

const int addAngle = 10;
const float PI = 3.14159265;
/*
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
}*/
Mesh::Mesh(Vector3 v, float l)
{
                   center = Vector3(v);
                   edgeLength = l;
                   rotatedAngle = Vector3(0,0,0);
                   sumAngle = 0;
}

void Mesh::drawFace() {
/*	for (int i = 0; i < (int) this->face.size(); ++i) {
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
	*/
	glPushMatrix();  
	glTranslatef (center.x, center.y, center.z); 
    glutSolidCube (edgeLength);
    glPopMatrix();
     
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
            for(int i = 0;i<vertex.size();i++)
                    vertex[i] = Vector3(vertex[i].x,-vertex[i].z,vertex[i].y);
            for(int i = 0;i<this->normalVec.size();i++)
                    normalVec[i] = Vector3(normalVec[i].x,-normalVec[i].z,normalVec[i].y);
            center = Vector3(center.x,-center.z,center.y);
     }       
     if(xyz == 2)
     {
            for(int i = 0;i<vertex.size();i++)
                    vertex[i] = Vector3(vertex[i].z,vertex[i].y,-vertex[i].x);
            for(int i = 0;i<this->normalVec.size();i++)
                    normalVec[i] = Vector3(normalVec[i].z,normalVec[i].y,-normalVec[i].x);
            center = Vector3(center.z,center.y,-center.x);
     }
     if(xyz == 3)
     {
            for(int i = 0;i<vertex.size();i++)
                    vertex[i] = Vector3(-vertex[i].y,vertex[i].x,vertex[i].z);
            for(int i = 0;i<this->normalVec.size();i++)
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
     this->drawFace();
	 glPopMatrix();
    }
    else drawFace();
}
