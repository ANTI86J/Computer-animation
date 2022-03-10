#include "stdafx.h"
#include <GL/glut.h>
#include <math.h>
#define pi 3.14159265358979


// screen width and height
int screenWidth;
int screenHeight;


// user initialization
GLfloat Velocity_New[10][3];
GLfloat Velocity_Old[10][3]={{2,0,0},{-2,0,0}};;
GLfloat Position_New[10][3];
GLfloat Position_Old[10][3]; 
GLfloat TimeStep=0.02f; 
static GLfloat M[16]={0}; //the matrix for glMatrixMult
GLfloat MR[10][16]; //the matrix for each ball
GLfloat acc[3]={0,-1.0,0}; // acceleration of gravity
GLfloat e=0.3f; //coefficient of restitution
int BallNumber=10; //The number of the balls
GLfloat LocationArray[10][3]={{-3.0f,6.0f,2.1f},{9.0f,0.5f,2.0f},{4.0f,7.0f,2.1f},{4.3f,6.0f,2.5f},{3.0f,6.0f,2.0f},{5.0f,9.0f,2.1f},{4.0f,11.0f,2.1f},{4.0f,10.0f,2.5f},{0.0f,6.0f,2.0f},{0.0f,7.3f,2.5f}};

//normalise the vector
void Normalise(GLfloat InterArray[3]){ 
	GLfloat m2 = InterArray [0] * InterArray [0] + InterArray [1] * InterArray [1] + InterArray [2] * InterArray [2];
	if (m2!=0 && (fabs(m2-1.0f)>0.00001f)){
		GLfloat m = sqrt(m2);
		InterArray[1] /= m;
		InterArray[2] /= m;
		InterArray[0] /= m;
	}
	
} 

//Dot product of two vectors
GLfloat DotProduct (GLfloat Vector2[3],GLfloat Vector1[3]){
	return Vector2[0]*Vector1[0]+Vector2[1]*Vector1[1]+Vector2[2]*Vector1[2];
}

//Compute the distances between two balls
GLfloat Distance (GLfloat Vector1[3],GLfloat Vector2[3]){
	
	GLfloat Distance=sqrt((Vector1[0]-Vector2[0])*(Vector1[0]-Vector2[0])+(Vector1[1]-Vector2[1])*(Vector1[1]-Vector2[1])+(Vector1[2]-Vector2[2])*(Vector1[2]-Vector2[2]));
	return Distance;

}

// user initialization
void init() 
{
	for (int j=0;j<BallNumber;j++){
		MR[j][0]=1.0f;
		MR[j][5]=1.0f;		
		MR[j][10]=1.0f;
		for (int i=0;i<3;i++){
			MR[j][12+i]=LocationArray[j][i];
			Position_Old[j][i]=MR[j][12+i];
		}
		MR[j][15]=1.0f;
	}
}

// Detect whether the ball Num have collision with other balls, methods are from NeHe's opengl tutorial-----lesson 30
void CollisionDetect(int Num){
	for (int i=Num+1;i<BallNumber;i++){
		if (Distance(Position_Old[Num],Position_Old[i])<1.01){ //Distance between two balls less than the diameter means the two balls occours collision
			
			
			GLfloat X_Axis[3];
			for(int j=0;j<3;j++){
				X_Axis[j]=Position_Old[i][j]-Position_Old[Num][j];
			}
			Normalise(X_Axis);


			//
			GLfloat Temp=DotProduct(X_Axis,Velocity_Old[Num]);
			GLfloat U1_X[3], U1_Y[3];
			for(int j=0;j<3;j++){
				U1_X[j]=Temp*X_Axis[j];
				U1_Y[j]=Velocity_Old[Num][j]-U1_X[j];
			}
			
			//
			for(int j=0;j<3;j++){
				X_Axis[j]=Position_Old[Num][j]-Position_Old[i][j];
			}
			Normalise(X_Axis);
			Temp=DotProduct(X_Axis,Velocity_Old[i]);
			GLfloat U2_X[3], U2_Y[3];
			for(int j=0;j<3;j++){
				U2_X[j]=Temp*X_Axis[j];
				U2_Y[j]=Velocity_Old[i][j]-U2_X[j];
			}

			GLfloat V1_X[3], V2_X[3];
			for(int j=0;j<3;j++){
				V1_X[j]=(U1_X[j]+U2_X[j]-(U1_X[j]-U2_X[j]))*0.5;
				V2_X[j]=(U1_X[j]+U2_X[j]-(U2_X[j]-U1_X[j]))*0.5;
				Velocity_Old[Num][j]=V1_X[j]+U1_Y[j];
				Velocity_Old[i][j]=V2_X[j]+U2_Y[j];
			}
			continue;



		}

	}
}

// the movement function of the Ball Num
void BallMovement(int Num){
	
	
		if(Position_Old[Num][1]<0.5){ // floor collision detection
			
			Velocity_Old[Num][1]=-e*Velocity_Old[Num][1];
			Velocity_Old[Num][0]=Velocity_Old[Num][0];
			Velocity_Old[Num][2]=Velocity_Old[Num][2];
			Position_Old[Num][1]=0.5;
			
		}
		CollisionDetect(Num);
		for (int i=0;i<3;i++){
			Velocity_New[Num][i]=Velocity_Old[Num][i]+acc[i]*TimeStep;
			Velocity_Old[Num][i]=Velocity_New[Num][i];
			Position_New[Num][i]=Position_Old[Num][i]+Velocity_New[Num][i]*TimeStep;
			Position_Old[Num][i]=Position_New[Num][i];
			MR[Num][12+i]=Position_New[Num][i];
				
		}
	
}

//Single ball display
void Ball1Display (int Num){  

	glPushMatrix();
	BallMovement(Num);
	for (int i=0;i<16;i++){
		M[i]=MR[Num][i];
	}
	glMultMatrixf(M);
	glutSolidSphere(0.5,20,20);
	glPopMatrix();

}

//All Ball Display
void AllDisplay(){

	for (int i=0;i<BallNumber;i++){
		Ball1Display (i);
	}
}

//Display the land
void LandDisplay(){
	glBegin(GL_LINES);
	for (GLfloat x = -100; x < 100;x+=0.2f)
	        {glVertex3f(x, 0, -100); glVertex3f(x, 0,  100);}         
	for (GLfloat z = -150; z < 100;z+=0.2f)
	        {glVertex3f(-150, 0, z); glVertex3f( 100, 0, z);}          
    glEnd();
}


void timer( int value ) {
	
	
	glutPostRedisplay();

	// reset timer
	// 16 ms per frame ( about 60 frames per second )
	//glutTimerFunc( 16, timer, 0 );
	
	
	glutTimerFunc( 16, timer, 0 );
}


void display( void ) {
	// clear buffer
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClearDepth (1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	// render state
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	
	// light source attributes
	GLfloat LightAmbient[]	= { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat LightDiffuse[]	= { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat LightSpecular[]	= { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat LightPosition[] = { 5.0f, 5.0f, 5.0f, 1.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT , LightAmbient );
	glLightfv(GL_LIGHT0, GL_DIFFUSE , LightDiffuse );
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);



	// surface material attributes
	GLfloat material_Ka[]	= { 0.11f, 0.06f, 0.11f, 1.0f };
	GLfloat material_Kd[]	= { 0.43f, 0.47f, 0.54f, 1.0f };
	GLfloat material_Ks[]	= { 0.33f, 0.33f, 0.52f, 1.0f };
	GLfloat material_Ke[]	= { 0.1f , 0.0f , 0.1f , 1.0f };
	GLfloat material_Se		= 10;

	glMaterialfv(GL_FRONT, GL_AMBIENT	, material_Ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE	, material_Kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR	, material_Ks);
	glMaterialfv(GL_FRONT, GL_EMISSION	, material_Ke);
	glMaterialf (GL_FRONT, GL_SHININESS	, material_Se);

	
	// modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt (0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	LandDisplay();
	AllDisplay();
	
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	
	// swap back and front buffers
	glutSwapBuffers();
	

}

// update viewport and projection matrix when the window is resized
void reshape( int w, int h ) {
	// viewport

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	// projection matrix

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(70.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);

	screenWidth  = w;
	screenHeight = h;
	
}

// keyboard input
void keyboard( unsigned char key, int x, int y ) {
	switch( key ) {
	case VK_ESCAPE:
		exit(0);
		break;

	default:
		break;
	}
}

int main( int argc, char** argv ) {
	// create GL window
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
	glutInitWindowSize(800, 600); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("lab2 application");

	// user initialization
	init ();
	
	// set callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(16, timer, 0);
	
	// main loop
	glutMainLoop();

	return 0;
}
