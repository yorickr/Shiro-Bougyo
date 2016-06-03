#include <iostream>
#include "Camera.h"
#include "WiiHandler.h"
#include "MenuModel.h"


MenuModel::MenuModel(WiiHandler * wiihandler, string filename) : ObjModel(filename)
{
//	this->camera = cam;
	this->wiiHandler = wiihandler;
}

MenuModel::~MenuModel()
{
}

void MenuModel::draw()
{
	ObjModel::draw();
}

void MenuModel::update(float deltatime)
{
}

void MenuModel::SetPositionMenu(float x, float y, float rotx, float roty)
{
	xpos = x;
	ypos = y;
	zpos = rotx;
	yrot =roty;
}
