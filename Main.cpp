//#include "stdafx.h"

#include <stdio.h>
#include <gl/glut.h>
 #include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Bcurve.hpp"
std::vector<glm::vec3> points;
 
 
Bcurve B;

// Get the width of the screen
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
// set the size of the screen
GLint windowWidth = 800;
GLint windowHeight = 600;
GLfloat xTran = 0.0f, yTran = 0.0f, zTran = 0.0f;
// angle rotated by x
GLfloat xRotAngle = 0.0f;
// angle rotated by y
GLfloat yRotAngle = 0.0f;

GLfloat TorsoHeight = 0.0f;// When squat down
GLfloat ArmRotAngle = 0.0f;//ÊTwist arm
GLfloat LegRotAngle = 0.0f;// Twist leg
 
 
GLUquadric *q;
 
 


  
 
float armL1 = 0, armL2 = 0, armR1 = 0, armR2 = 0, legL1 = 0, legL2 = 0, legR1 = 0, legR2 = 0;
// 8 places to be rotated
 


 
// Draw heads
void DrawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();

 
	glColor3f(0.343, 0.443, 0.33443);
	glTranslatef(xPos, yPos, zPos);
	glTranslatef(0, 1, 0);
    glutSolidSphere(10.0f, 30, 30);
	glPopMatrix();
}

// Draw body
void DrawTorso(float xPos, float yPos, float zPos)
{
	glPushMatrix();

 
	glColor3f(0.443, 0.443, 0.354);
	glTranslatef(xPos, yPos, zPos);
	glPushMatrix();
	glScalef(15, 25, 10);   // The body of this object is a 3*5*2 cubium
 
	
  

	glBegin(GL_QUADS);
	// front
 
	glVertex3f(-1.0f, -1.0f, 1.0f);
 
	glVertex3f(1.0f, -1.0f, 1.0f);
 
	glVertex3f(1.0f, 1.0f, 1.0f);
 
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	 
	glBegin(GL_QUADS);
	// back
 	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glVertex3f(1.0f, 1.0f, -1.0f);
	
	glVertex3f(1.0f, -1.0f, -1.0f);
	// top

	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	glVertex3f(-1.0f, 1.0f, 1.0f);
	
	glVertex3f(1.0f, 1.0f, 1.0f);
	 
	glVertex3f(1.0f, 1.0f, -1.0f);
	// bottom
	
	glVertex3f(-1.0f, -1.0f, -1.0f);
 
	glVertex3f(1.0f, -1.0f, -1.0f);
	
	glVertex3f(1.0f, -1.0f, 1.0f);
	
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

 
	glBegin(GL_QUADS);
	// right
	glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
	// left
    glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	
	 
 	glPopMatrix();
    glPushMatrix();
    glPopMatrix();

 
	glPopMatrix();
}

// Draw arm
void DrawArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glTranslatef(xPos, yPos, zPos);
	glColor3f(0.4443, 0.34243, 0.1354);
 
	glPushMatrix();
    glTranslatef(0, 11, 0);
    glRotatef(90, 1, 0, 0);
    gluCylinder(q, 6,5,26, 12, 12);
	 	 
    gluSphere(q, 6, 12, 12);
 

	glPopMatrix();
	 
	glPopMatrix();
}
// Draw small arm
void DrawSmallArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	 
	glTranslatef(xPos, yPos, zPos);
 
	glColor3f(0.2443, 0.4443, 0.354);
	//glutSolidCube(5.0f);
	glPushMatrix(); 
	glTranslatef(0, 15, 0);
	glRotatef(90, 1, 0, 0);
	gluCylinder(q, 5, 3, 30, 12, 12);
	gluSphere(q, 5, 12, 12);
 

				
	glPopMatrix();
	glTranslatef(0, -14, 0);

	glPushMatrix();

	 
	glScalef(1.5, 3.5, 1);
	glutSolidCube(3.0);
	glPopMatrix();
	 
	glPopMatrix();
} 


 
// Draw leg
void DrawLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
	glColor3f(0.4443, 0.764443, 0.98354);
    glPushMatrix();
		
    glTranslatef(0, 10, -3);
    gluSphere(q, 6.5, 14, 14);
    glPopMatrix	();

 
	glTranslatef(xPos, yPos, zPos);
	

 

 
	glScalef(6.50f, 17.0f, 6.50f);   // The leg of this object is a 1*3*1 Cubium
 
	glBegin(GL_QUADS);
	// front
	
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	
	glVertex3f(1.20f, 1.0f, 1.0f);

	glVertex3f(-1.20f, 1.0f, 1.0f);
	glEnd();
	glBegin(GL_QUADS);
	// back
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glVertex3f(1.20f, 1.0f, -1.0f);
	
	glVertex3f(1.20f, -1.0f, -1.0f);
	// top
    
	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	
	glVertex3f(1.0f, 1.0f, -1.0f);
	// back
	
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glVertex3f(1.0f, -1.0f, -1.0f);
	
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

 
	glBegin(GL_QUADS);
	// right
	glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
	// left
    glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
 



 



	glPopMatrix();
}
void DrawShank(float xPos, float yPos, float zPos)
{
	glPushMatrix();
 
	glColor3f(0.5443, 0.75443, 0.354);
	glTranslatef(xPos, yPos, zPos);
	glScalef(7, 40.0f,7);   // The leg of this object is a 1*6*1 cubium
	 
	glutSolidCube(1.0f);
	glPopMatrix();
	glPushMatrix();


	//Draw shoes
	glTranslatef(0, -20, 5);
	glScalef(8, 8, 18);
 
	glutSolidCube(1.0f);
	glPopMatrix();
}
  
GLboolean barml1 = GL_TRUE, barml2 = GL_TRUE, barmr1 = GL_TRUE, barmr2 = GL_TRUE, blegl1 = GL_TRUE, blegl2 = GL_TRUE, blegr1 = GL_TRUE, blegr2 = GL_TRUE;
 
void human(   float ArmRotAngle, float LegRotAngle)
{
	glPushMatrix();
 
	glScalef(0.5, 0.5, 0.5);
	// Head motionless
	DrawHead(0.0f, 60.0f  , 0.0f);
	// The trunk sinks and rises
	DrawTorso(0.0f, 25.0f , 0.0f);
    
	//////////////////////////////////////////////////////////////////////////////
	glPushMatrix();//  Draw the ball. The ball needs to be with the hand, so you have to do the same thing
 

	glPopMatrix();
    
//////////////////////////////////////////////////////////////////////////////////


	//ÊDraw the arm, size is 10*30*10
	glPushMatrix(); // First move the coordinates to the highest point of the arm, and then rotate
	glTranslatef(-20.0f, 50.0f  , 0.0f);
	glRotatef(armL1, 1.0f, 0.0f, 0.0f);// rotate the arm
	//printf("%f", armL1);
//	glRotatef(armL1, -1, 0, 0);
	glTranslatef(0.0f, -15.0f, 0.0f);
	 
	DrawArm(0.0f, 0.0f, 0.0f);// Now draw the arm

	glTranslatef(0.0f, -15.0f, 0.0f);
 	glRotatef(armL2, 1, 0, 0);
	glTranslatef(0.0f, -15.0f, 0.0f);
	DrawSmallArm(0.0f, 0.0f, 0.0f);

	glTranslatef(0, -25, -5);
	 
 
	glPopMatrix();

	glPushMatrix();// First move the coordinates to the highest point of the arm, and then rotate
	glTranslatef(20.0f, 50.0f , 0.0f);
 	glRotatef(armR1, 1, 0, 0);
	glTranslatef(0.0f, -15.0f, 0.0f);
	DrawArm(0.0f, 0.0f, 0.0f);// Draw the arm

	glTranslatef(0.0f, -15.0f, 0.0f);
 
	glRotatef(armR2, 1, 0, 0);
	glTranslatef(0.0f, -15.0f, 0.0f);
	DrawSmallArm(0.0f, 0.0f, 0.0f);
 

 


	glPopMatrix();

	//ÊDraw the arm, size is 10*30*10

	glPushMatrix();
	glTranslatef(-5.0f, 0.0f , 0.0f);// First fix the root of the thigh in the position of the body, the direction of rotation
 	glRotatef(legL1, 1, 0, 0);
	glTranslatef(-3.0f, -15.0f, 0.0f);// Then move the coordinates of the drawing thigh down half the distance to draw the thigh
	DrawLeg(0.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -15.0f, 0.0f);
	glRotatef(legL2, 1, 0, 0);
 	glTranslatef(0.0f, -15.0f, 0.0f);
	DrawShank(0.0f, 0.0f, 0.0f);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0f, 0.0f , 0.0f);// First fix the root of the thigh in the position of the body, the direction of rotation
 	glRotatef(legR1, 1, 0, 0);
	glTranslatef(3.0f, -15.0f, 0.0f);// Then move the coordinates of the drawing thigh down half the distance to draw the thigh
	DrawLeg(0.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, -15.0f, 0.0f);
	glRotatef(legR2, 1, 0, 0);
 	glTranslatef(0.0f, -15.0f, 0.0f);
	DrawShank(0.0f, 0.0f, 0.0f);

	glPopMatrix();


	glPopMatrix();

	glPopMatrix();
}

 
int idx = 0;
float tanx = -120;
// Display the callback function
void renderScreen(void){
	// Clear the window color to be black
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	// Clear the entire window to the current clear color: black; Clear the depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	// Draw a point and rotate
    // The current matrix is set to the model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Resets the currently specified matrix to the identity matrix
	gluLookAt(0, 100, 400, 0, 0, 0, 0, 1, 0);

	//glPopMatrix();


	//Pushes the current Matrix state onto the stack
	glPushMatrix();
 
  
 	 
  
 
	 

	// The coordinate system rotates yRotAngle about the y axis
	 
	glRotatef(yRotAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(xRotAngle, 1.0f, 0.0f, 0.0f);
	// Smooth out


	 
	//glTranslatef(tanx, 0, 0);

	glLineWidth(10.0);
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);

	for (int i = 0; i < idx; i++)
	{
		glVertex3fv(&B.curve.Verts[i][0]);
	}

	glEnd();

    if (idx >= B.curve.Verts.size())
    {
		 idx = 0;
	}
		 
    vec3 p = B.curve.Verts[idx++];
    // Calculate the position of this point to make the turn
    float angle =atan2(p.x , p.z);
    glTranslatef(p.x, p.y+30, p.z );
    glRotatef(angle * 180 / 3.1415926 +90, 0, 1, 0);
    human( ArmRotAngle, LegRotAngle);
	 
	


	// Restores the matrix pushed on the stack
	glPopMatrix();
 
	// Swaps Pointers to two buffers
	glutSwapBuffers();
}

//Response to the key press action

void pressKey(unsigned char key, int x, int y)
{
	 

	// re-draw
	glutPostRedisplay();
}


// set the Redering State
void setupRederingState(void){
	glEnable(GL_DEPTH_TEST);	// Enables the program to be deeply tested
 
  	glFrontFace(GL_CCW); // The counterclockwise direction of a polygon is front
    
  	glEnable(GL_CULL_FACE); // Do not show back
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); // The back and front sides are filled with lines
 
	glShadeModel(GL_SMOOTH);

	 
	glEnable(GL_AUTO_NORMAL);
	
 
 
	q = gluNewQuadric();
 
 
 
}

// Window size change callback function
void changSize(GLint w, GLint h){
	// Horizontal width ratio
	GLfloat ratio;

	GLfloat coordinatesize = 200.0f;
	// Window width height zero returns directly
	if ((w == 0) || (h == 0))
		return;
	// Set the viewport to be the same size as the window
	glViewport(0, 0, w, h);
	// Apply the subsequent matrix operations to the projection matrix
	glMatrixMode(GL_PROJECTION);
	// Resets the currently specified matrix to the identity matrix
	glLoadIdentity();
	ratio = (GLfloat)w / (GLfloat)h;
    //gluPerspective(60, ratio, 0.1, 10000);
    
	// Orthogonal projection
    gluPerspective(60, ratio, 0.1, 200000);
    // if (w<h)
    //	glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
    // else
    //	glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);

	
}

// Key input processing callback function
void specialKey(int key, int x, int y){

	if (key == GLUT_KEY_UP){
		xRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_DOWN){
		xRotAngle += 5.0f;
	}
	else if (key == GLUT_KEY_LEFT){
		yRotAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_RIGHT){
		yRotAngle += 5.0f;
	}
	// re-draw
	glutPostRedisplay();
}
float vt = 0.0;
 
void timerFunc(int value)
{	
 
	
 
	{	
 
  

		if (barml1)
		{
			armL1 -= 1;
			if (armL1 < -30)
				barml1 = !barml1;
		}
		else
		{
			armL1 += 1;
			if (armL1 > 30)
				barml1 = !barml1;
		}


		if (barml2)
		{
			armL2 += 0.1;
			if (armL2 > 0)
				barml2 = !barml2;
		}
		else
		{
			armL2 -= 0.1;
			if (armL2 < -20)
				barml2 = !barml2;
		}


		if (barmr1)
		{
			armR1 += 1;
			if (armR1 > 30)
				barmr1 = !barmr1;
		}
		else
		{
			armR1 -= 1;
			if (armR1 < -30)
				barmr1 = !barmr1;
		}


		if (barmr2)
		{
			armR2 +=0.1;
			if (armR2 > 0)
				barmr2 = !barmr2;
		}
		else
		{
			armR2 -= 0.1;
			if (armR2 < -20)
				barmr2 = !barmr2;
		}






		if (blegl1)
		{
			legL1 += 1;
			if (legL1 > 30)
				blegl1 = !blegl1;
		}
		else
		{
			legL1 -= 1;
			if (legL1 < -30)
				blegl1 = !blegl1;
		}


		if (blegl2)
		{
			legL2 += 0.1;
			if (legL2 >30)
				blegl2 = !blegl2;
		}
		else
		{
			legL2 -= 0.1;
			if (legL2 < 50)
				blegl2 = !blegl2;
		}

		if (!blegr1)
		{
			legR1 +=1;
			if (legR1 > 30)
				blegr1 = !blegr1;
		}
		else
		{
			legR1 -=1;
			if (legR1 < -30)
				blegr1 = !blegr1;
		}


		if (blegr2)
		{
			legR2 += 0.1;
			if (legR2 > 50)
				blegr2 = !blegr2;
		}
		else
		{
			legR2 -= 0.1;
			if (legR2 < 30)
				blegr2 = !blegr2;
		}

 
	}
	 
	 glutPostRedisplay();
	glutTimerFunc(50, timerFunc, 1);
}

void idle()
{
 	glutPostRedisplay();


}
void init()
{
	points.push_back(vec3(100, 0, -100)); // Add initial point
	points.push_back(vec3(-120, 0, -100)); // Add initial point
	points.push_back(vec3(-100, 0, 120)); // Add initial point
	points.push_back(vec3(120, 0, 100));// // Add initial point
	points.push_back(vec3(100, 0, -100)); // Add initial point

	B.init(points);
	B.draw();

}
int main(int argc, char* argv[])
{
	// Menu
	GLint iMainMenu;
	GLint iCoordinateaxisMenu;
	GLint iOrthoOrPerspectMenu;
	//Initialize glut
	glutInit(&argc, argv);
	//ÊUse double buffer, depth buffer.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Gets the wide pixels of the system
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	// Gets the height pixels of the system
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
 	glutCreateWindow("Main");
	// set the size of the window
	glutReshapeWindow(windowWidth, windowHeight);
	// The window is displayed in the center
	glutPositionWindow((SCREEN_WIDTH - windowWidth) / 2, (SCREEN_HEIGHT - windowHeight) / 2);
	// A function that handles window size changes
	glutTimerFunc(50, timerFunc, 1);

	glutReshapeFunc(changSize);
	// Set global render parameters
	setupRederingState();
	// Set the display callback function
	glutDisplayFunc(renderScreen);
	// Sets the key input processing callback function
	glutSpecialFunc(specialKey);
	glutKeyboardFunc(pressKey);
	glutIdleFunc(idle);
	init();
	
 	
	glutMainLoop();

	return 0;
}


