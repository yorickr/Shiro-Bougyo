#include <iostream>
#include "Camera.h"
#include "WiiHandler.h"
#include "MenuModel.h"

MenuModel::MenuModel(Camera * cam, WiiHandler * wiihandler,string filename): ObjModel(filename)
{
	this->camera = cam;
	this->wiiHandler = wiihandler;
	playButton = new ObjModel("models/buttons/playbutton.obj");
	playButton->xpos = -6;
	playButton->ypos = 2.7;
	playButton->zpos = 6.5;
	playButton->xrot = 0;
	playButton->yrot = 30;
	/*settingsButton = new ObjModel("models/buttons/settings-button.obj");
	exitButton = new ObjModel("models/buttons/exit-button.obj");*/
}

MenuModel::~MenuModel()
{
}

void MenuModel::draw()
{
	ObjModel::draw();
	playButton->draw();
	//settingsButton->draw();
	//exitButton->draw();
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
