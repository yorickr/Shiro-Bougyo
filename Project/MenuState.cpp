#include "MenuState.h"
#include "Camera.h"
#include "MenuModel.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

//int crosshairX, crosshairY;

void MenuState::Init(GameStateManager * game, Camera * cam, WiiHandler * hand)
{
	this->manager = game;
	this->camera = cam;
	this->wiiHandler = hand;
//	crosshairX = camera->width/2;
//	crosshairY = camera->height/2;
}

void MenuState::Cleanup()
{
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::HandleEvents()
{

}

void MenuState::Update()
{
//	DrawCrosshair(camera->width/2,camera->height/2);
}

/*void MenuState::DrawCrosshair(int x, int y){

	glPushMatrix();
	glTranslatef((float)3, 0.0f, (float)3);
	glPointSize(10);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f(crosshairX, crosshairY);
	glEnd();
	glPopMatrix();
}*/

void MenuState::Draw()
{
	/*glPushMatrix();
	glTranslatef((float)3, 0.0f, (float)3);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);

	glColor3f(1, 1, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);

	glColor3f(0, 0, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(-1, -1, 1);

	glColor3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, -1, 1);

	glColor3f(0, 1, 0);
	glVertex3f(-1, -1, -1);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(-1, -1, 1);

	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();
<<<<<<< HEAD
	glPopMatrix();*/

//	DrawCrosshair(camera->width/2,camera->height/2);
//Make StartMenu and push to models vector
	MenuModel->draw();
	glPopMatrix();

	//DrawCrosshair(camera->width/2,camera->height/2);
}

void MenuState::preDraw()
{

}
