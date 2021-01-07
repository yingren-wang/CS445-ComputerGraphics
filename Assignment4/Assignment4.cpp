//////////////////////////////////////////////////////////////////////         
// Assignment4.cpp
//
// This program draws a teapot with lightings.
//
// Interaction:
// "Press 's' to toggle the specular light off/on."
// "Press 'd' to toggle the diffuse light off/on."
// "Press '+' to increase shininess value by 5" 
// "Press '-' to decrease shininess value by 5"
// "Press ',' to move the light by .5 unit in positive z direction"
// "Press '.' to move the light by .5 unit in negative z direction"
// "Press arrow keys to rotate the white light about the original position of the ball."
//
// Yingren Wang
////////////////////////////////////////////////////////////////////// 

#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

// Globals.
static int difOn = 0;
static int specOn = 0;
static float diffuse = 1.0;
static float specular = 1.0;
static float m = 0.2; // Global ambient white light intensity.
static int localViewer = 1; // Local viewpoint?
static float p = 1.0; // Positional light?
static float xAngle = 0.0, yAngle = 0.0; // Rotation angles of white light.
static float zDistance = 3.0;
static int shininess = 50.0;

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // clear the background to white
	glEnable(GL_DEPTH_TEST); // Enable depth testing.

	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);

	// Material property vectors.
	float matAmbAndDif[] = { 0.9, 0.2, 0.2, 1.0 };
	float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties of ball.
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
}

// Drawing routine.
void drawScene()
{
	// Change Shininess
	float matShine[] = { shininess };
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDif[] = { diffuse, diffuse, diffuse, 1.0 };
	float lightSpec[] = { specular, specular, specular, 1.0 };
	float lightPos0[] = { 0.0, 0.0, zDistance, p };
	float globAmb[] = { m, m, m, 1.0 };

	// Lights properties.
	// glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpec);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer); // Enable local viewpoint

	// Turn lights off/on.
	if (difOn) glEnable(GL_LIGHT1); else glDisable(GL_LIGHT1);
	if (specOn) glEnable(GL_LIGHT2); else glDisable(GL_LIGHT2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Draw light source spheres (or arrow) after disabling lighting.
	glDisable(GL_LIGHTING);

	// Lights positioned 
	glPushMatrix();
	glRotatef(xAngle, 1.0, 0.0, 0.0); // Rotation about x-axis.
	glRotatef(yAngle, 0.0, 1.0, 0.0); // Rotation about y-axis.
	// glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos0);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos0);
	glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
	glPopMatrix();

	glEnable(GL_LIGHTING);

	// Teapot
	glFrontFace(GL_CW);
	glutSolidTeapot(1.0);
	glFrontFace(GL_CCW);

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 20.0);
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
	case 's':
		// enable/disable specular lighting components
		if (difOn) difOn = 0; else difOn = 1;
		glutPostRedisplay();
		break;
	case 'd':
		// enable/disable diffuse lighting components
		if (specOn) specOn = 0; else specOn = 1;
		glutPostRedisplay();
		break;
	case '+':
		// increase shininess value by 5
		shininess += 5.0;
		glutPostRedisplay();
		break;
	case '-':
		// decrease shininess value by 5
		shininess -= 5.0;
		glutPostRedisplay();
		break;
	case '.':
		// move the light by .5 unit in negative z direction
		zDistance -= 0.5;
		glutPostRedisplay();
		break;
	case ',':
		// move the light by .5 unit in positive z direction
		zDistance += 0.5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_DOWN)
	{
		xAngle += 0.5;
		if (xAngle > 360.0) xAngle -= 360.0;
	}
	if (key == GLUT_KEY_UP)
	{
		xAngle -= 0.5;
		if (xAngle < 0.0) xAngle += 360.0;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		yAngle += 0.5;
		if (yAngle > 360.0) yAngle -= 360.0;
	}
	if (key == GLUT_KEY_LEFT)
	{
		yAngle -= 0.5;
		if (yAngle < 0.0) yAngle += 360.0;
	}
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press 's' to toggle the specular light off/on." << std::endl
		<< "Press 'd' to toggle the diffuse light off/on." << std::endl
		<< "Press '+' to increase shininess value by 5" << std::endl
		<< "Press '-' to decrease shininess value by 5" << std::endl
		<< "Press ',' to move the light by .5 unit in positive z direction" << std::endl
		<< "Press '.' to move the light by .5 unit in negative z direction" << std::endl
		<< "Press arrow keys to rotate the white light about the original position of the ball." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("lightAndMaterial2.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

