#include <iostream>
#include "Camera.h"
#include "WiiHandler.h"
#include "MenuModel.h"

MenuModel::MenuModel(Camera * cam, WiiHandler * wiihandler): ObjModel("models/Menu/Menu.obj")
{
	this->camera = cam;
	this->wiiHandler = wiihandler;
	playButton = new ObjModel("models/buttons/play-button");
	settingsButton = new ObjModel("models/buttons/settings-button");
	exitButton = new ObjModel("Models/buttons/exitbutton");
	ypos = -20;
}

void MenuModel::draw()
{
	ObjModel::draw();
}

void MenuModel::update()
{
	
}
