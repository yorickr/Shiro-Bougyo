#pragma once
#pragma once
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"

class GameState;

class ButtonModel :
	public ObjModel
{
public:
	ButtonModel(Camera * camera, WiiHandler * wiiHandler, GameState * state, string filename);
	~ButtonModel();
	void draw() override;
	void update(float deltatime) override;
	//void update(float deltatime, bool *keys) override;
private:
	Camera * camera;
	WiiHandler * wiiHandler;
	GameState * state;
};
