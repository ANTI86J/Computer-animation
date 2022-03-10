#include <GL/freeglut.h>
#include "simulation.h"

Config config;

vec2 windowSize = config.windowSize;
Simulation simulation = Simulation(&config);

int lastTime;
float deltaTime;
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	simulation.draw();
	glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-windowSize.x/2, windowSize.x/2, -windowSize.y/2, windowSize.y/2, -1.0, 100.0);
    glOrtho(-windowSize.x, windowSize.x, -windowSize.y, windowSize.y, -1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle() {
    // update delta time
    int time = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = static_cast<float>(time-lastTime) / 1000.0;
    lastTime = time;

    simulation.update(deltaTime);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowSize.x, windowSize.y);
    //glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowSize.x)/2, (glutGet(GLUT_SCREEN_HEIGHT) - windowSize.y)/2);
    //glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowSize.x), (glutGet(GLUT_SCREEN_HEIGHT) - windowSize.y));
	glutCreateWindow("Boids");
	//glutSetCursor(GLUT_CURSOR_NONE);

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
