//////////////////////////////////////////////////////////////////////         
// Assignment2.cpp
//
// This program is a mini game. The goal is to move the sphere into the square
// When the goal is reached, the game is terminated
//
// Interaction:
// Press A to move sphere left 10 units
// Press D to move sphere right 10 units
// Press W to move sphere up 10 units
// Press S to move sphere down 10 units
//
// Yingren Wang
////////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <cmath>
#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h> 

#define PI 3.14159265

// Globals.

// cursor X and Y positions
static float cursorX = 0.0;
static float cursorY = 0.0;

// color info
int colorR;
int colorG;
int colorB;

// boolean to detect whether the triangles need to be reflected
bool isReflected = false;

// variable to store what kind of brush
enum brushes
{
	CURSOR, CUBE, SPHERE, TRIANGLE
};

// brush info
brushes brushArray[4] = {CURSOR, CUBE, SPHERE, TRIANGLE};
std::string brushNames[4] = { "CURSOR", "CUBE", "SPHERE", "TRIANGLE" };
int brushIndex = 0; // represent current brush's index in the brushArray
brushes brush = CURSOR; // current brush

// class shape, includs brush type, position, and color for the shape
class Shape{
public:
	brushes b;
	float x;
	float y;
	int rC;
	int	gC;
	int bC;
	Shape(brushes bT, float xP, float yP, int rC, int gC, int bC);
	void drawShape();
};

// vector storing all the previously drawn shapes
std::vector<Shape> drawnShapes;

// constructor for the class shape
Shape::Shape(brushes bType, float xPosition, float yPosition, int red, int green, int blue) {
	b = bType;
	x = xPosition;
	y = yPosition;
	rC = red;
	gC = green;
	bC = blue;
}

// function to draw the shape to the canvas
void Shape::drawShape() {
	glColor3ub(rC, gC, bC);
	switch (b) {
	case CURSOR: 
		break;
	case CUBE:
		// draw the wired cube
		glPushMatrix();
		glTranslatef(x, y, -50.0);
		glutWireCube(5.0); // draw a cube with 50 as the size
		glPopMatrix();
		break;
	case SPHERE:
		// draw the wired sphere
		glPushMatrix();
		glTranslatef(x, y, -50.0);
		glutWireSphere(2.5, 8, 2); // draw a sphere with 15 as the radius
		glPopMatrix();
		break;
	case TRIANGLE:
		// draw the triangle
		glPushMatrix();
		glTranslatef(x, y, -50.0);
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 2.5, 0.0);
		glVertex3f(2.5, -2.5, 0.0);
		glVertex3f(-2.5, -2.5, 0.0);
		glEnd();
		glPopMatrix();
		break;
	}
}

// funtions to print out sentenses
void writeBitmapString(void *font, char *string)
{
	char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Front faces filled, back faces outlined.
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	// Block to reflect the scene about the yz-plane.
	if (isReflected)
	{
		glFrontFace(GL_CW);
	}
	else
	{
		glFrontFace(GL_CCW);
	}
	
	// draw all the previous drawn shapes
	for (int i = 0; i < drawnShapes.size(); i++) {
		drawnShapes.at(i).drawShape();
	}

	// char array for brush info output
	char printChar[32];

	// write the cursor information
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos3f(-4.5, -4.5, -5.0);
	std::string printString = "BRUSH: " + brushNames[brushIndex];
	strcpy(printChar, printString.c_str());
	writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, printChar);
	glPopMatrix();

	// draw the cursor
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex3f(cursorX, cursorY, -50.0); // draw a cursor with 5.0 as the point size
	glEnd();
	glPopMatrix();

	// generate random color
	srand(time(NULL));
	colorR = rand() % 256;
	colorG = rand() % 256;
	colorB = rand() % 256;
	
	glutSwapBuffers();
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
	gluPerspective(90, 1.0, 5.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	// control sphere movement using adws
	case 'a':
		cursorX -= 5.0;
		glutPostRedisplay();
		break;
	case 'd':
		cursorX += 5.0;
		glutPostRedisplay();
		break;
	case 'w':
		cursorY += 5.0;
		glutPostRedisplay();
		break;
	case 's':
		cursorY -= 5.0;
		glutPostRedisplay();
		break;
	// switch between front and back
	case 'o':
		if (isReflected) isReflected = false;
		else isReflected = true;
		glutPostRedisplay();
		break;
	case '+': // change brush type
		if (brushIndex >= 0 && brushIndex < 3) {
			brushIndex++;
			brush = brushArray[brushIndex];
		}
		else if (brushIndex >= 3) {
			brushIndex = 1;
			brush = brushArray[brushIndex];
		}
		glutPostRedisplay();
		break;
	case ' ': // "draw" shape by adding them to the drawnShapes vector
		Shape s(brush, cursorX, cursorY, colorR, colorG, colorB);
		drawnShapes.push_back(s);
		glutPostRedisplay();
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Use AWSD to control cursor go left, up, down, and right" << std::endl;
	std::cout << "Use o to switch the direction of the face of the traingle" << std::endl;
	std::cout << "Use space to draw the cursor indicted shape to the canvas" << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("rotatingHelix3.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
