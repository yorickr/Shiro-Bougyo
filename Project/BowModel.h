#pragma once
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"
#include "AnimatedModel.h"

class BowModel :
	public ObjModel
{
public:
	BowModel( WiiHandler * wiiHandler, string filename);
	~BowModel();
	void draw() override;
	float toRadian(float degree);
	void update() override;
private:
	ObjModel * crosshair;
	void SetPositions(float x, float y, float rotx, float roty);
	void setCrosshairPositions(float x, float y, float rotx, float roty);
	WiiHandler * wiiHandler;
	float bowPostion = 0.8;

	void CalcBoundingSpheres() override;

	void InitBoundingSpheres() override;
};

