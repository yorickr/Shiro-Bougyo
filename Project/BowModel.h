#pragma once
#include "ObjModel.h"
#include "Camera.h"
class BowModel :
	public ObjModel
{
public:
	BowModel(Camera * camera);
	~BowModel();
	void SetPositions(float x, float y, float rotx, float roty);
	void draw() override;
	float toRadian(float degree);
	void update() override;
private:
	Camera * camera;

};

