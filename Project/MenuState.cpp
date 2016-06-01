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
	//crosshairX = camera->width/2;
	//crosshairY = camera->height/2;
	cam->posX = 0;
	cam->posY = 0;
	MenuModel * menu = new MenuModel(cam,hand,"models/Menu/Menu.obj");
	cam->posX = 3.7;
	cam->posY = -5;
	cam->posZ = -12;
	cam->rotX = 0;
	cam->rotY = 34;

	models.push_back(pair<int, ObjModel*>(1, menu));
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

void MenuState::Update(float deltatime)
{
	//DrawCrosshair(camera->width/2,camera->height/2);
	for (auto &m : models) {
		m.second->draw();
	}
}

void MenuState::Update(float deltatime, bool * keys)
{
	//DrawCrosshair(camera->width/2,camera->height/2);
	for (auto &m : models) {
		m.second->draw();
	}
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
	glPushMatrix();

	//DrawCrosshair(camera->width/2,camera->height/2);
	
	//Make StartMenu and push to models vector
	for (auto &m : models) {
		m.second->draw();
	}
	glPopMatrix();
}

void MenuState::preDraw()
{

}

void MenuState::AddModel(CollisionModel *model) {

}

void MenuState::DeleteModel(CollisionModel* model)
{

}
