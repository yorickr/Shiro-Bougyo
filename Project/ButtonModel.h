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
	ButtonModel( WiiHandler * wiiHandler, GameState * state, string filename);
	~ButtonModel();
	void draw() override;
	void update(float deltatime) override;
	//void update(float deltatime, bool *keys) override;
	void SetPositions(float x, float y, float z, float rotx, float roty);
private:
	Camera * camera;
	WiiHandler * wiiHandler;
	GameState * state;
};
