#include "ButtonModel.h"
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"

ButtonModel::ButtonModel(Camera * camera, WiiHandler * wiiHandler, GameState * state, string filename):ObjModel(filename)
{
	this->camera = camera;
	this->wiiHandler = wiiHandler;
	this->state = state;
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
