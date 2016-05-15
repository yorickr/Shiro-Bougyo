#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <ApplicationServices/ApplicationServices.h>
#include <cstdlib>
#include "wiiuse.h"

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "GameStateManager.h"
#include "Camera.h"

GameStateManager gameManager;
int width, height;
bool keys[255];

void onDisplay() {
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float)width / height, 0.1, 50);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, 0, camera.posY);


	glColor3f(0.5f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(-15, -1, -15);
	glVertex3f(15, -1, -15);
	glVertex3f(15, -1, 15);
	glVertex3f(-15, -1, 15);
	glEnd();
	gameManager.Draw();
	glutSwapBuffers();
}

void onIdle() {




}

void onTimer(int id){

	if(keys[27]) exit(0);
	if(keys['w']) camera.posY++;
	if(keys['s']) camera.posY--;
	if(keys['d']) camera.posX--;
	if(keys['a']) camera.posX++;

	gameManager.Update();
	glutPostRedisplay();
	glutTimerFunc(1000/60,onTimer, 1);
}

void onKeyboard(unsigned char key, int, int) {
	switch (key)
	{
		case 27:             // ESCAPE key
			exit (0);
		case '[':
			gameManager.previousState();
			break;
		case ']':
			gameManager.nextState();
			break;
		default:
			//just to please CLion.
			break;
	}
	gameManager.HandleEvents(key);
	keys[key] = true;
}

void onKeyboardUp(unsigned char key, int, int) {
	keys[key] = false;
}

void mousePassiveMotion(int x, int y) {

	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(width / 2, height / 2);
	}
}

void test(){

	wiimote** wiimotes;
	int found, connected;

	/*
	 *	Initialize an array of wiimote objects.
	 *
	 *	The parameter is the number of wiimotes I want to create.
	 */
	wiimotes =  wiiuse_init(4);

	/*
	 *	Find wiimote devices
	 *
	 *	Now we need to find some wiimotes.
	 *	Give the function the wiimote array we created, and tell it there
	 *	are MAX_WIIMOTES wiimotes we are interested in.
	 *
	 *	Set the timeout to be 5 seconds.
	 *
	 *	This will return the number of actual wiimotes that are in discovery mode.
	 */
	found = wiiuse_find(wiimotes, 4, 5);
	if (!found) {
		printf("No wiimotes found.\n");
		return;
	}
}

int main(int argc, char* argv[]) {
	gameManager.Init();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("Shiro Bougyo");

	glEnable(GL_DEPTH_TEST);
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
    //Needed for osx
    #ifdef __APPLE__
    CGSetLocalEventsSuppressionInterval(0.0);
    #endif

	glutIdleFunc(onIdle);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(onKeyboard);
	glutTimerFunc(1000/60,onTimer, 1);
	glutKeyboardUpFunc(onKeyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(width / 2, height / 2);

	memset(keys, 0, sizeof(keys));

	test();

	glutMainLoop();
}
