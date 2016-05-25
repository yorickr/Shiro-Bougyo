#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <ApplicationServices/ApplicationServices.h>
#include <cstdlib>

#else
#include <windows.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include "GL\freeglut.h"
#endif

#include "GameStateManager.h"
#include "SerialHandler.h"
#include "Camera.h"

#include "WiiHandler.h"

#define COMMPORT 4
#define DELTATIME_MODIFIER 1000;

GameStateManager gameManager;
SerialHandler serial = SerialHandler(COMMPORT);
bool keys[255];
void* wiiFunc(void * argument);
Camera camera;
WiiHandler wiiHandler;
int buttonPressed = 0;
int WindowWidth = 1920;
int WindowHight = 1080;

int oldTimeSinceStart;

void onDisplay() {
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)WindowWidth / WindowHight, 0.1,100);

	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();

	//load bow
	gameManager.preDraw();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posZ,camera.posY);
	gameManager.Draw();
	// Process all OpenGL routine s as quickly as possible

	glFlush();
	glutSwapBuffers();
}

void initializeThreads(){
	std::thread wiiThread(&wiiFunc,nullptr); //WiiMote Thread
	wiiThread.detach();
	std::thread serialThread(&SerialHandler::receiveThread, &serial); //Serialthread
	serialThread.detach();
}

void onIdle() {
	glutPostRedisplay();
}

void onTimer(int id) {
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float deltatime = oldTimeSinceStart - timeSinceStart *  DELTATIME_MODIFIER;
	gameManager.Update(deltatime);
	glutTimerFunc(1000 / 60, onTimer, 1);
}

void onKeyboard(unsigned char key, int, int) {
	switch (key)
	{
	case 27:             // ESCAPE key
		exit(0);
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
	keys[key] = true;
}

void* wiiFunc(void * argument) {
	wiiHandler.wiiMoteTest(&camera);
	return 0;
}

void onKeyboardUp(unsigned char key, int, int) {
	keys[key] = false;
}

void mousePassiveMotion(int x, int y) {
		int dx = x - WindowWidth / 2;
		int dy = y - WindowHight / 2;
		if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
		{
			camera.rotX += dy / 10.0f;
			if (camera.rotX > 30) {
				camera.rotX = 30;
			}
			else if (camera.rotX < -30) {
				camera.rotX = -30;
			}
			camera.rotY += dx / 10.0f;
			glutWarpPointer(WindowWidth / 2, WindowHight / 2);
		}
}


void mouseFunction(int button,int state, int mouse_x, int mouse_y)
{
	buttonPressed = state == GLUT_LEFT_BUTTON;
	if(buttonPressed)
	{
		//gameManager.nextState();
		printf("pressed x: %i/n", mouse_x);
		printf("pressed y: %i/n", mouse_y);
	}
}

void mouseFunc(int button, int state, int x, int y) {
    printf("Received %d %d \n", button, state);
    if (button == 0 && state == 1) {
        //Tell gamestatemanager to shoot arrow

    }
}


int main(int argc, char* argv[]) {
	initializeThreads();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(WindowWidth,	WindowHight);
	glutCreateWindow("Shiro Bougyo");

	glEnable(GL_DEPTH_TEST);
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
#if __APPLE__
	CGSetLocalEventsSuppressionInterval(0.0);
#endif
	glutIdleFunc(onIdle);
	glutDisplayFunc(onDisplay);
	glutReshapeFunc([](int w, int h) { WindowWidth = w; WindowHight = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(onKeyboard);
	glutTimerFunc(1000 / 60, onTimer, 1);
	
	glutKeyboardUpFunc(onKeyboardUp);
	
	//glutMotionFunc(mouseFunction);
	glutMouseFunc(mouseFunction);
	glutPassiveMotionFunc(mousePassiveMotion);
    glutMouseFunc(mouseFunc);
	
	glutWarpPointer(WindowWidth / 2, WindowHight / 2);
	memset(keys, 0, sizeof(keys));
	
	gameManager.Init(&camera, &wiiHandler);

	glutMainLoop();
}
