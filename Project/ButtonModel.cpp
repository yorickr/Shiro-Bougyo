#include "ButtonModel.h"
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"

ButtonModel::ButtonModel(Camera * camera, WiiHandler * wiiHandler, GameState * state, string filename):ObjModel(filename)
{
	this->camera = camera;
	this->wiiHandler = wiiHandler;
	this->state = state;
	SetPositions(0, 0, 0, 0, 0);
}

ButtonModel::~ButtonModel()
{
}

void ButtonModel::draw()
{
	ObjModel::draw();
}

void ButtonModel::update(float deltatime)
{
	ObjModel::update(deltatime);
}

void ButtonModel::SetPositions(float x, float y, float z, float rotx, float roty)
{
	xpos = x;
	ypos = y;
	zpos = z;
	xrot = rotx;
	yrot = roty;
}
