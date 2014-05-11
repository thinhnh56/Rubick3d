#include <Windows.h>
#include <iostream>
#include "Camera.h"
#include "gl/glut.h"
#include <gl/gl.h>
#include "Mesh.h"

using namespace std;

const int HEIGHT = 640;
const int WIDTH = 480;
const char* TITLE = "Rubik";

Camera camera;
float angle = 1;
Mesh m;

void modelRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

}

void keyboardFunc(unsigned char key, int x, int y) {

	switch (key) {
	case 'd':
	case 'D':
		camera.move(Vector3(0, 1, 0));
		break;
	case 'w':
	case 'W':
		camera.move(Vector3(1, 0, 0));
		break;
	case 'a':
	case 'A':
		camera.move(Vector3(0, -1, 0));
		break;
	case 's':
	case 'S':
		camera.move(Vector3(1, 0, 0));
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 150);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow(TITLE);

	// Register callback
	glutDisplayFunc(modelRender);

	glutMainLoop();
	return 0;
}
