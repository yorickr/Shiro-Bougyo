#pragma once
#include "ObjModel.h"
#include "Camera.h"
class BowModel :
	public ObjModel
{
public:
	BowModel(Camera * camera);
	void SetPositions();
	~BowModel();
	void draw() override;
	float toRadian(float degree);
	void update() override;
private:
	Camera * camera;
};

