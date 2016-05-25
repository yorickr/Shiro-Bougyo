#include <iostream>
#include "Camera.h"
#include "WiiHandler.h"
#include "MenuModel.h"


MenuModel::MenuModel(Camera * cam, WiiHandler * wiihandler,string filename): ObjModel(filename)
{
	this->camera = cam;
	this->wiiHandler = wiihandler;
	playButton = new ObjModel("models/buttons/playbutton.obj");
	settingsButton = new ObjModel("models/buttons/settingsButton.obj");
	exitButton = new ObjModel("models/buttons/ExitButton.obj");
	mouseCursor = new ObjModel("models/mouseCursor/mouseCursor.obj");
	SetButtonPosition(-6.2, 2.7, 6.5, 0, 30,playButton);
	SetButtonPosition(-6.2, 2.2, 6.5, 0, 30, settingsButton);
	SetButtonPosition(-6.2, 1.7, 6.5, 0, 30, exitButton);
	//int x = mousePointer.x;
	//int y = mousePointer.y;
	//SetPositionMouse(x,y,mouseCursor);
	printf("button x: %f/n", playButton->xpos);
	printf("button y: %f/n", playButton->ypos);
	//printf("Motion233 y: %i/n", mousePointer.y);
}

MenuModel::~MenuModel()
{
}

void MenuModel::draw()
{
	ObjModel::draw();
	playButton->draw();
	settingsButton->draw();
	exitButton->draw();
}

void MenuModel::update()
{
}

void MenuModel::SetPositionMenu(float x, float y, float rotx, float roty)
{
	xpos = x;
	ypos = y;
	zpos = rotx;
	yrot =roty;
}

void MenuModel::SetButtonPosition(float xpos, float ypos, float zpos, float xrot, float yrot, ObjModel *model)
{
	model->xpos = xpos;
	model->ypos = ypos;
	model->zpos = zpos;
	model->xrot = xrot;
	model->yrot = yrot;
}

void MenuModel::SetPositionMouse(int x, int y, ObjModel *model)
{
    model->xpos = x;
	model->ypos = y;
}
