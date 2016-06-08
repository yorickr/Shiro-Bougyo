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

#include "PlayingState.h"

#include "WiiHandler.h"

#define COMMPORT 5
#define DELTATIME_MODIFIER 10;

#include "sdl_audio.h"

GameStateManager gameManager;
SerialHandler serial = SerialHandler(COMMPORT, &gameManager);

bool keys[255];
void* wiiFunc(void * argument);
//Camera camera;

WiiHandler wiiHandler;
int buttonPressed = 0;
int WindowWidth = 1920;
int WindowHeight = 1080;

int oldTimeSinceStart = 0;

void onDisplay() {
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0f, (float)WindowWidth / WindowHight, 0.1,100);
//
//
//	glMatrixMode(GL_MODELVIEW);
//
//
//	glLoadIdentity();

    //load bow

//	gameManager.preDraw();
//	glRotatef(camera.rotX, 1, 0, 0);
//	glRotatef(camera.rotY, 0, 1, 0);
//	glTranslatef(camera.posX, camera.posY, camera.posZ);
//	gameManager.Draw();

    // Process all OpenGL routine s as quickly as possible

	gameManager.Draw();



    glFlush();
    glutSwapBuffers();
}

void initializeThreads(){
	std::thread wiiThread(&wiiFunc, nullptr); //WiiMote Thread
	wiiThread.detach();
	std::thread musicThread(&SDL_Audio::playTheme, SDL_Audio()); //Play theme sound
	musicThread.detach();
	std::thread serialThread(&SerialHandler::receiveThread, &serial); //Serialthread
	serialThread.detach();
}

void onIdle() {
	glutPostRedisplay();
}

void onTimer(int id) {
	if (keys[27]) exit(0);
	if (keys['m']) { //Scale powerup.
		GameState* currentState = gameManager.getCurrentState();
		PlayingState *playState = dynamic_cast<PlayingState*>(currentState);
		if (playState)
			playState->ScalePowerUp();
	}
	if (keys['n']) { //
		GameState* currentState = gameManager.getCurrentState();
		PlayingState *playState = dynamic_cast<PlayingState*>(currentState);
		if (playState)
			playState->DestoryPowerUp();
	}

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	//for testing remove keys for final release:
	float deltatime = (timeSinceStart - oldTimeSinceStart) /  DELTATIME_MODIFIER;
	oldTimeSinceStart = timeSinceStart;
	//TODO: for testing remove keys for final release:
	bool t = keys['t'];
	gameManager.Update(deltatime, t);
	oldTimeSinceStart = timeSinceStart;
	//gameManager.Update(deltatime);
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
		//if(wiiHandler.wiiMoteP1 != 0 && wiiHandler.wiiMoteP1->exp.type == EXP_NUNCHUK){
			gameManager.nextState();
		//}
		break;
	default:
		//just to please CLion.
		break;
	}
	keys[key] = true;
}

void* wiiFunc(void * argument) {
	//wiiHandler.wiiMoteLoop();
	return 0;
}

void onKeyboardUp(unsigned char key, int, int) {
	keys[key] = false;
}

void mousePassiveMotion(int x, int y) {
		int dx = x - WindowWidth / 2;
		int dy = y - WindowHeight / 2;
		if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
		{
			gameManager.GetPlayers().at(0)->getCamera()->rotX += dy / 10.0f;
			if (gameManager.GetPlayers().at(0)->getCamera()->rotX > 30) {
				gameManager.GetPlayers().at(0)->getCamera()->rotX = 30;
			}
			else if (gameManager.GetPlayers().at(0)->getCamera()->rotX < -30) {
				gameManager.GetPlayers().at(0)->getCamera()->rotX = -30;
			}
			gameManager.GetPlayers().at(0)->getCamera()->rotY += dx / 10.0f;
			glutWarpPointer(WindowWidth / 2, WindowHeight / 2);
		}
}


void mouseFunction(int button,int state, int mouse_x, int mouse_y)
{
	buttonPressed = state == GLUT_LEFT_BUTTON;
	if(buttonPressed)
	{
		//gameManager.nextState();
		//printf("pressed x: %i/n", mouse_x);
		//printf("pressed y: %i/n", mouse_y);
	}
}

void mouseFunc(int button, int state, int x, int y) {
    //printf("Received %d %d \n", button, state);
    if (button == 0 && state == 1) {
        //Tell gamestatemanager to shoot arrow

    }
}

void windowReshape(int w, int h){
	WindowWidth = w;
	WindowHeight = h;
	gameManager.width = w;
	gameManager.height = h;
	for ( auto &player : gameManager.GetPlayers()) {
		player->getCamera()->width = w;
		player->getCamera()->height = h;
	}
}


int main(int argc, char* argv[]) {
	initializeThreads();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);
	glutInitWindowSize(WindowWidth,	WindowHeight);
	glutCreateWindow("Shiro Bougyo");

	glEnable(GL_DEPTH_TEST);
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
#if __APPLE__
	CGSetLocalEventsSuppressionInterval(0.0);
#endif
    glutIdleFunc(onIdle);
    glutDisplayFunc(onDisplay);
	glutReshapeFunc(windowReshape);
    glutKeyboardFunc(onKeyboard);
    glutTimerFunc(1000 / 60, onTimer, 1);

    glutKeyboardUpFunc(onKeyboardUp);
    glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(WindowWidth / 2, WindowHeight / 2);
	memset(keys, 0, sizeof(keys));

	gameManager.Init(&wiiHandler);
	gameManager.addSerialHandler(&serial);

	glutMainLoop();
}
