#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <ApplicationServices/ApplicationServices.h>
#include <cstdlib>

#include <iostream>
#include <pthread.h>
#include <iostream>
#include "wiiuse/src/wiiuse.h"

#else
#include <windows.h>
#include "GL\freeglut.h"
#include "wiiuse/src/wiiuse.h"
#endif
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

#include "GameStateManager.h"
#include "Camera.h"
#include "WiiHandler.h"

GameStateManager gameManager;
bool keys[255];
void* wiiFunc(void * argument);
Camera camera;

void onDisplay() {
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float)camera.width / camera.height, 0.1, 50);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, 0, camera.posY);


	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-15, -1, -15);
	glVertex3f(15, -1, -15);
	glVertex3f(15, -1, 15);
	glVertex3f(-15, -1, 15);
	glEnd();
	glPopMatrix();
	
	glColor3f(1.0f, 1.0f, 1.0f);
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

void* wiiFunc(void * argument){
	WiiHandler hand;
	hand.wiiMoteTest(&camera);
	return 0;
}

void onKeyboardUp(unsigned char key, int, int) {
	keys[key] = false;
}

void mousePassiveMotion(int x, int y) {

	int dx = x - camera.width / 2;
	int dy = y - camera.height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(camera.width / 2, camera.height / 2);
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
	glutReshapeFunc([](int w, int h) { camera.width = w; camera.height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(onKeyboard);
	glutTimerFunc(1000/60,onTimer, 1);
	glutKeyboardUpFunc(onKeyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(camera.width / 2, camera.height / 2);

	memset(keys, 0, sizeof(keys));


	//pthread_t wiiThread;


	//pthread_create(&wiiThread, NULL, wiiFunc, NULL);

	glutMainLoop();
}
