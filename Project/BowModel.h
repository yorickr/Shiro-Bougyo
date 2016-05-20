#pragma once
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"

class BowModel :
	public ObjModel
{
public:
	BowModel( WiiHandler * wiiHandler);
	~BowModel();
	void draw() override;
	float toRadian(float degree);
	void update() override;
private:
	Camera * camera;
	ObjModel * crosshair;
	void SetPositions(float x, float y, float rotx, float roty);
	void setCrosshairPositions(float x, float y, float rotx, float roty);
	WiiHandler * wiiHandler;
	float bowPostion = 0.8;
};

