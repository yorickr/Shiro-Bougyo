#pragma once
#include "ObjModel.h"
#include "Camera.h"
#include "WiiHandler.h"

class BowModel :
	public ObjModel
{
public:
	BowModel(Camera * camera, WiiHandler * wiiHandler);
	~BowModel();
	void SetPositions(float x, float y, float rotx, float roty, int wiiX, int wiiY);
	void draw() override;
	float toRadian(float degree);
	void update() override;
private:
	Camera * camera;
	WiiHandler * wiiHandler;
};

