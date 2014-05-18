/* Module      : MainFile.cpp
 * Author      : Chu Van Tao
 * Email       : 
 * Course      : Computer Graphics
 *
 * Description : 
 *
 *
 * Date        : 
 *
 * History:
 * Revision      Date          Changed By
 * --------      ----------    ----------
 * 01.00         ?????          ???
 * First release.
 *
 */

/* -- INCLUDE FILES ------------------------------------------------------ */
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

#include "Mesh.h"
#include "Vector3.h"

using namespace std;

/* -- DATA STRUCTURES ---------------------------------------------------- */

/* -- GLOBAL VARIABLES --------------------------------------------------- */

const float PI = 3.1416;
float distanceToOrigin = 5;
float phi,theta;
float ex ,ey ,ez ;
float dx ,dy ,dz ;

Vector3 m_start, m_end;
GLdouble wx, wy, wz;  /*  returned world x, y, z coords  */
GLdouble wx1, wy1, wz1;  /*  returned world x, y, z coords  */
        
/* -- LOCAL VARIABLES ---------------------------------------------------- */


/*A position 2d of mouse is a ray in world view.
 *This function create this ray (2 points in ray) 
 */
void makeRayPicking(int x, int y)
{
   GLint viewport[4];
   GLdouble mvmatrix[16], projmatrix[16];
   GLint realy;  /*  OpenGL y coordinate position  */
   
   glGetIntegerv(GL_VIEWPORT, viewport);
   glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
   glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
/*  note viewport[3] is height of window in pixels  */
    realy = viewport[3] - (GLint) y - 1;
    printf("Coordinates at cursor are (%4d, %4d)\n", 
               x, realy);
    gluUnProject((GLdouble) x, (GLdouble) realy, 0.0,
               mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
               
    m_start.set((float)wx,(float) wy,(float) wz);
    printf("World coords at z=0.0 are (%f, %f, %f)\n",
               m_start.x, m_start.y, m_start.z);
               
    gluUnProject((GLdouble) x, (GLdouble) realy, 1.0,
               mvmatrix, projmatrix, viewport, &wx1, &wy1, &wz1);
               
    m_end.set((float)wx1,(float) wy1,(float) wz1);
    printf("World coords at z=1.0 are (%f, %f, %f)\n",     
               m_end.x, m_end.y, m_end.z);
         
}

/*
double collisionRayAndMesh (Mesh mesh) // return -1 if not, k > 0 if true with k is smallest distance from start to collisionPoints
{
     // mesh have center and egde length
     Vector3 center; // = mesh.center;
     double egdeLength; // = mesh.egdeLength;
     Vector3 normalVectorPlane[] = {{0,0,1} , {0,0,-1} , {0,1,0} , {0,-1,0} , {1,0,0} , {-1,0,0}};
     Vector3 centerPlane;
     
     Vector3 rayU = m_end - m_start;
     Vector3 pointCollision;
     double dst = 10000000.0;
     bool collison = false;
     for (int i = 0;i < 6 ; i ++)
     {
         centerPlane = center + normalVectorPlane[i] .product( egdeLength/2);
         
         double k;
         k = ((centerPlane - m_start) .dot( normalVectorPlane[i])) / (rayU .dot( normalVectorPlane[i]));
         pointCollision = m_start + k* rayU;
         
         Vector3 vetorCollision = pointCollision - centerPlane;
         if( fabs(vetorCollision. x) < 1 && fabs(vetorCollision. y) < 1 && fabs(vetorCollision. z) < 1)
         {
             collison = true;
             double dist = pointCollision.Distance(m_start);
             if(dist < dst) dst = dist;
         }
                                      
     }
     if(collison) return dst;
     return -1;
     
     
     
}

int idOfSelectedMesh(vector<Mesh> mesh)
{
        double minDistToStart = 10000000.0;
        int meshID = -1;
        for(int i = 0;i< mesh.size() ;i++)
        {
                double dst = collisionRayAndMesh (mesh[i]);
                if( dst > 0)
                {
                    if (dst < minDistToStart)
                    {
                            minDistToStart = dst;
                            meshID = i;
                    }
                                       
                }
        }
        return meshID;
        
}

*/

void mouse(int button, int state, int x, int y) 
{
   GLint viewport[4];
   GLdouble mvmatrix[16], projmatrix[16];
   GLint realy;  /*  OpenGL y coordinate position  */
   
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            makeRayPicking(x,y);
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
/* ----------------------------------------------------------------------- */
/* Function    : void setWindow( GLint x,GLint y,GLint z,GLint t )
 *
 * Description : set a window to draw and use for glViewport
 *
 * Parameters  : 
 *
 * Returns     : void
 */

void setWindow( GLdouble x,GLdouble y,GLdouble z,GLdouble t )  {
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D( x, y, z, t );
}


/* ----------------------------------------------------------------------- */
/* Function    : void myInit( )
 *
 * Description : Initialize OpenGL and the window where things will be
 *               drawn.
 *
 * Parameters  : void
 *
 * Returns     : void
 */

void myInit()  {
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glColor3f( 0.0, 0.0, 0.0 );
  glPointSize( 6.0 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  glOrtho (-2, 2, -2, 2, 0, 10);
  glMatrixMode( GL_MODELVIEW );
  phi = PI/6;
  theta = PI/4;
  
  
}



/* ----------------------------------------------------------------------- */
/* Function    : void myDisplay( void )
 *
 * Description : This function gets called everytime the window needs to
 *               be redrawn.
 *
 * Parameters  : void
 *
 * Returns     : void
 */

void myDisplay( void )  {
     glClear(GL_COLOR_BUFFER_BIT);   // Erase everything
     glLoadIdentity();
	
 	 ez = distanceToOrigin * cos(phi);
     ex = distanceToOrigin * sin(phi)*sin(theta);
     ey = distanceToOrigin * sin(phi)*cos(theta);
     dx = -cos (phi) * sin (theta);
     dy = -cos (phi) * cos (theta);
     dz = sin (phi);
     gluLookAt (ex,ey,ez, 0, 0, 0, dx, dy, dz);
	 glBegin(GL_LINES);
	// glVertex3f(wx,wy,wz);
	 //glVertex3f(wx1,wy1,wz1);
	 glVertex3f(-2,0,0);
	 glVertex3f(2,0,0);
	 glVertex3f(0,2,0);
	 glVertex3f(0,-2,0);
	 glVertex3f(0,0,2);
	 glVertex3f(0,0,-2);
	 glEnd();
	 
	 glPushMatrix();
     glTranslatef (1, 0, 0); 
	 glutWireCube (0.5);
	 
	 glTranslatef (-2, 0, 0);
	 glutWireSphere (0.5, 20, 20);
	 glPopMatrix();
	 
	// Sleep(100);
	 glutPostRedisplay();
     glFlush();
}

/* ----------------------------------------------------------------------- */
/* Function    : void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
 *
 * Description : Control by keyboard
 *
 * Parameters  : void
 *
 * Returns     : void
 */

void myKeyboard(unsigned char theKey,int,int)
{
  
  switch(theKey)
  {
                case 'u':
                     phi -= PI/100;                     
                     break;
                case 'd':
                     phi += PI/100;                     
                     break;
                     break;
                case 'l':
                     theta -= PI/100;                     
                     break;
                case 'r':
                     theta += PI/100;                     
                     break;
                     break;
                case 'e': exit(-1); //terminate the program
                default: break; // do nothing
  }
}


/* ----------------------------------------------------------------------- */
/* Function    : int main( int argc, char** argv )
 *
 * Description : This is the main function. It sets up the rendering
 *               context, and then reacts to user events.
 *
 * Parameters  : int argc     : Number of command-line arguments.
 *               char *argv[] : Array of command-line arguments.
 *
 * Returns     : int : Return code to pass to the shell.
 */

int main( int argc, char *argv[] )  {
  // Initialize GLUT.
  glutInit( &argc, argv );
  // Set the mode to draw in.
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  // Set the window size in screen pixels.
  glutInitWindowSize( 600, 600 );
  // Set the window position in screen pixels.
  glutInitWindowPosition( 150, 150 );
  // Create the window.
  glutCreateWindow( "press u,d,l,r to control camera" );
  // Set the callback funcion to call when we need to draw something.
  
  glutDisplayFunc(myDisplay);
  glutMouseFunc(mouse);
  glutKeyboardFunc(myKeyboard);
  
  myInit();
  // Now that we have set everything up, loop responding to events.
  glutMainLoop( );
  
}

/* ----------------------------------------------------------------------- */

