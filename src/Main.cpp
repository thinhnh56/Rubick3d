#include "stdafx.h"
#include "Mesh.h"
#include "Vector3.h"

const int HEIGHT = 600;
const int WIDTH = 600;

using namespace std;

const float PI = 3.1416;
float distanceToOrigin = 350;
float phi, theta;
float ex, ey, ez;
float dx, dy, dz;

Vector3 m_start, m_end;
GLdouble wx, wy, wz; /*  returned world x, y, z coords  */
GLdouble wx1, wy1, wz1; /*  returned world x, y, z coords  */
Mesh m;
vector<Mesh> mesh;

int id = -1;
Vector3 position;

/*A position 2d of mouse is a ray in world view.
 *This function create this ray (2 points in ray)
 */
void makeRayPicking(int x, int y) {
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realy; /*  OpenGL y coordinate position  */

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	/*  note viewport[3] is height of window in pixels  */
	realy = viewport[3] - (GLint) y - 1;
	printf("Coordinates at cursor are (%4d, %4d)\n", x, realy);
	gluUnProject((GLdouble) x, (GLdouble) realy, 0.0, mvmatrix, projmatrix,
			viewport, &wx, &wy, &wz);

	m_start.set((float) wx, (float) wy, (float) wz);
	printf("World coords at z=0.0 are (%f, %f, %f)\n", m_start.x, m_start.y,
			m_start.z);

	gluUnProject((GLdouble) x, (GLdouble) realy, 1.0, mvmatrix, projmatrix,
			viewport, &wx1, &wy1, &wz1);

	m_end.set((float) wx1, (float) wy1, (float) wz1);
	printf("World coords at z=1.0 are (%f, %f, %f)\n", m_end.x, m_end.y,
			m_end.z);

}

double collisionRayAndMesh(Mesh mesh) // return -1 if not, k > 0 if true with k is smallest distance from start to collisionPoints
		{
	// mesh have center and egde length
	Vector3 center = mesh.center;
	double egdeLength = mesh.edgeLength;
	Vector3 normalVectorPlane[] = { Vector3(0, 0, 1), Vector3(0, 0, -1),
			Vector3(0, 1, 0), Vector3(0, -1, 0), Vector3(1, 0, 0), Vector3(-1,
					0, 0) };
	Vector3 centerPlane;

	Vector3 rayU = m_end - m_start;
	Vector3 pointCollision;
	double dst = 10000000.0;
	bool collison = false;
	for (int i = 0; i < 6; i++) {
		centerPlane = center + normalVectorPlane[i] * (egdeLength / 2.0);

		double k;
		k = ((centerPlane - m_start) * (normalVectorPlane[i]))
				/ (rayU * (normalVectorPlane[i]));
		pointCollision = m_start + rayU * k;

		glBegin(GL_POINTS);
		glVertex3f(pointCollision.x, pointCollision.y, pointCollision.z);
		glEnd();
		Vector3 vetorCollision = pointCollision - centerPlane;
		if (fabs(vetorCollision.x) < egdeLength / 2
				&& fabs(vetorCollision.y) < egdeLength / 2
				&& fabs(vetorCollision.z) < egdeLength / 2) {
			collison = true;
			double dist = pointCollision.Distance(m_start);
			if (dist < dst)
				dst = dist;
		}

	}
	if (collison)
		return dst;
	return -1;

}

int idOfSelectedMesh(vector<Mesh> mesh) {
	double minDistToStart = 10000000.0;
	int meshID = -1;
	for (int i = 0; i < (int) mesh.size(); i++) {
		cout << i << "\n";
		double dst = collisionRayAndMesh(mesh[i]);
		if (dst > 0) {
			if (dst < minDistToStart) {
				minDistToStart = dst;
				meshID = i;
			}

		}
	}
	return meshID;

}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			makeRayPicking(x, y);
			id = idOfSelectedMesh(mesh);
			cout << id;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			exit(0);
		break;
	default:
		break;
	}
}

void myInit() {
	// OpenGL init
	// Stuff
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	// Anh sang
	// Lighting
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 0.5
			, 0.5, 0.5, 1.0 };
	GLfloat light_position[] = { -200, -200.0, -200.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);

	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, WIDTH / HEIGHT, 0.1, 2000);
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

	phi = 0.989604;
	theta = -2.37191;

	m.getMesh("Rubik's Cube.obj");
	m.loadMtl("Rubik's Cube.mtl");
	for (int i = 0; i < (int) m.componentMesh.size(); i++) {
		m.componentMesh[i].materials = m.materials;
		m.componentMesh[i].computeCenter();
		mesh.push_back(m.componentMesh[i]);
	}
	//m.toString();
}

void drawCordinate() {
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(000, 0, 0);
		glVertex3f(120, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 120, 0);
		glVertex3f(0, 000, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 000);
		glVertex3f(0, 0, 120);
	}
	glEnd();
	glDisable(GL_COLOR_MATERIAL);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	ez = distanceToOrigin * cos(phi);
	ex = distanceToOrigin * sin(phi) * sin(theta);
	ey = distanceToOrigin * sin(phi) * cos(theta);
	dx = -cos(phi) * sin(theta);
	dy = -cos(phi) * cos(theta);
	dz = sin(phi);
	gluLookAt(ex, ey, ez, 0, 0, 0, dx, dy, dz);
	drawCordinate();
	for (int i = 0; i < (int) mesh.size(); i++) {
		mesh[i].drawMesh();
	}
	glutPostRedisplay();
	glFlush();
}

void myKeyboard(unsigned char theKey, int, int) {
	if (id >= 0) {
		float x = mesh[id].center.x;
		float y = mesh[id].center.y;
		float z = mesh[id].center.z;
		if (mesh[id].sumAngle == 0)
			switch (theKey) {
			case 'x':
				for (int i = 0; i < (int) mesh.size(); i++) {
					if (mesh[i].center.x == x) {
						cout << i << " ";
						cout << mesh[i].center.x << " " << mesh[i].center.y
								<< " " << mesh[i].center.z << "\n";
						mesh[i].rotateMesh(1);
						cout << mesh[i].center.x << " " << mesh[i].center.y
								<< " " << mesh[i].center.z << "\n";

					}
				}
				break;
			case 'y':
				for (int i = 0; i < (int) mesh.size(); i++) {
					if (mesh[i].center.y == y)
						mesh[i].rotateMesh(2);
				}
				//mesh[id].rotateMesh(1);
				break;
			case 'z':
				for (int i = 0; i < (int) mesh.size(); i++) {
					if (mesh[i].center.z == z)
						mesh[i].rotateMesh(3);
				}
				//mesh[id].rotateMesh(1);
				break;
			}
	}
	switch (theKey) {
	case 'w':
		phi -= PI / 100;
		break;
	case 's':
		phi += PI / 100;
		break;
	case 'd':
		theta -= PI / 100;
		break;
	case 'a':
		theta += PI / 100;
		break;
	case 'q':
		if (distanceToOrigin < 450)
			distanceToOrigin += 5;
		break;
	case 'e':
		if (distanceToOrigin > 300)
			distanceToOrigin -= 5;
		break;
	case ' ':
		exit(-1); //terminate the program
	default:
		break; // do nothing
	}
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Rubik");
	glViewport(0, 0, WIDTH, HEIGHT);
	// Assign Functions
	glutDisplayFunc(myDisplay);
	glutMouseFunc(mouse);
	glutKeyboardFunc(myKeyboard);

	myInit();
	// Now that we have set everything up, loop responding to events.
	glutMainLoop();

}

/* ----------------------------------------------------------------------- */
