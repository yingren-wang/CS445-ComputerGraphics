/////////////////////////////////////////////////////////////////////         
// assignment1.cpp
//
// This program draws sine wave defaultly and can switch between sine
// and cosine waves depending on the user. The larger the number of 
// vertices the better the loop approximates the actual sine/cosine wave.
//
// Interaction:
// Press +/- to increase/decrease the number of vertices of the loop. 
// Press space bar to switch between cosine and sine.
//
// Yingren Wang.
///////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

#define PI 3.14159265358979324

// Globals.
static int numVertices = 5; // Number of vertices on circle.
bool drawCos = false;

// Drawing routine.
void drawScene(void)
{
	// variable
	float i = 0.0;

	glClear(GL_COLOR_BUFFER_BIT);

	// y = x line
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 50.0, 0.0);
	glVertex3f(100.0, 50.0, 0.0);
	glEnd();

	// decide what to draw depending on the boollean
	if (drawCos == true) {
		// cosine line
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j <= numVertices; j++) {
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(i * 50.0 / PI, cos(i) * 50.0 + 50.0, 0.0);
			i += float(float(2.0 * PI) / float(numVertices - 1));
		}
		glEnd();
	}
	else {
		// sine line
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j <= numVertices; j++) {
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(i * 50.0 / PI, sin(i) * 50.0 + 50.0, 0.0);
			i += float(float(2.0 * PI) / float(numVertices - 1));
		}
		glEnd();
	}

	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	// exit
	case 27:
		exit(0);
		break;
	// increase num of vertices
	case '+':
		numVertices++;
		glutPostRedisplay();
		break;
	// reduce num of vertices
	case '-':
		if (numVertices > 3) numVertices--;
		glutPostRedisplay();
		break;
	// use the space bar to switch between sine and cosine
	case ' ':
		if (drawCos == true) drawCos = false;
		else drawCos = true;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press +/- to increase/decrease the number of vertices on the wave." << std::endl;
	std::cout << "Press space bar to switch between cosine and sine." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("assignment1.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
