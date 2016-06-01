#pragma once

#include "CollisionModel.h"

class WarriorModel :
	public CollisionModel
{
public:
	WarriorModel(float x, float z);
	~WarriorModel();
	void update(float deltatime) override;
	void InitBoundingSpheres() override;
	void setSize(int);
private:
	short right;
};

