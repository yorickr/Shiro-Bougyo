#pragma once
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"
#include "AnimatedModel.h"
#include "ArrowModel.h"


class GameState;

class BowModel :
	public ObjModel
{
public:
	BowModel( WiiHandler * wiiHandler, string filename, GameState * state, Camera * camera);
	~BowModel();
	void draw() override;
	float toRadian(float degree);
	void fireArrow();
	void update(float deltatime) override;
private:
	ObjModel * crosshair;
	GameState * state;
	Camera* camera_;
	ArrowModel * arrow;
	WiiHandler * wiiHandler;
	int counter = 0;
	void SetPositions(float x, float y, float rotx, float roty);
	void setCrosshairPositions(float x, float y, float rotx, float roty);
	void setArrowPosition();
	
	float bowPostion = 0.05;
	int wiiXPos = 0;
	int wiiYPos = 0;
};

