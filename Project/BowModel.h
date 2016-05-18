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
	void update() override;
private:
	Camera * camera;
};

