#pragma once
#include "ObjModel.h"
#include "Camera.h"
class BowModel :
	public ObjModel
{
public:
	BowModel(Camera * camera);
	~BowModel();
	
	void draw() override;
	float toRadian(float degree);
	void update() override;
private:
	Camera * camera;
	ObjModel * crosshair;
	void SetPositions(float x, float y, float rotx, float roty);
	void setCrosshairPositions(float x, float y, float rotx, float roty);
};

