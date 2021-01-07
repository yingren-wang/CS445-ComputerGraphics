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

#include <GL/glew.h>
#include <GL/freeglut.h> 

#define PI 3.14159265

// Globals.
// sphere X and Y positions
static float sphereX = 250.0;
static float sphereY = 250.0;

// cube X and Y positions
float cubeX;
float cubeY;

// count for animation across how many frames
int count = 5;

// boolean to detect whether the game has ended
bool hasWon = false;

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
	glColor3f(0.0, 0.0, 0.0);

	// draw wire cube
	glPushMatrix();
	glTranslatef(cubeX, cubeY, 0.0);
	glutWireCube(50.0); // draw a cube with 50 as the size
	glPopMatrix();

	// draw wire sphere
	glPushMatrix();
	glTranslatef(sphereX, sphereY, 0.0);
	glutWireSphere(15.0, 8, 2); // draw a sphere with 15 as the radius
	glPopMatrix();

	// check the position of the sphere
	if (sphereX <= cubeX + 25.0 && sphereX >= cubeX - 25.0 && sphereY <= cubeY + 25.0 && sphereY >= cubeY - 25.0) {
		glPushMatrix();
		glRasterPos3f(200.0, 250.0, 0.0);
		hasWon = true;
		writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "YOU WIN");
		glPopMatrix();
	}

	glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// generate random cube X and Y in the range [25, 475]
	srand(time(NULL));
	cubeX = float((rand() % (475 - 25 + 1)) + 25);
	cubeY = float((rand() % (475 - 25 + 1)) + 25);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 500.0, 0.0, 500.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Timer function to control movements
void moveLeft(int value)
{	
	if (sphereX >= 2.0 && count >= 1) {
		sphereX -= 2.0;
		glutTimerFunc(20, moveLeft, 1);
		count--;
	}
	glutPostRedisplay();
}

void moveRight(int value) {
	if (sphereX <= 488.0 && count >= 1) {
		sphereX += 2.0;
		glutTimerFunc(20, moveRight, 1);
		count--;
	}
	glutPostRedisplay();
}

void moveUp(int value) {
	if (sphereY <= 488.0 && count >= 1) {
		sphereY += 2.0;
		glutTimerFunc(20, moveUp, 1);
		count--;
	}
	glutPostRedisplay();
}

void moveDown(int value) {
	if (sphereY >= 2.0 && count >= 1) {
		sphereY -= 2.0;
		glutTimerFunc(20, moveDown, 1);
		count--;
	}
	glutPostRedisplay();
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
		if (hasWon == false) {
			glutTimerFunc(20, moveLeft, 1);
			count = 5;
		}
		break;
	case 'd':
		if (hasWon == false) {
			glutTimerFunc(20, moveRight, 1);
			count = 5;
		}
		break;
	case 'w':
		if (hasWon == false) {
			glutTimerFunc(20, moveUp, 1);
			count = 5;
		}
		break;
	case 's':
		if (hasWon == false) {
			glutTimerFunc(20, moveDown, 1);
			count = 5;
		}
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Use AWSD to control the player (sphere) to go left, up, down, and right" << std::endl;
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
