#pragma once
#include "CollisionModel.h"
class SecondWarriorModel :
	public CollisionModel
{
public:
	SecondWarriorModel(float x, float z);
	~SecondWarriorModel();
	void update(float deltatime) override;
	void InitBoundingSpheres() override;
	void setSize(int);
private:
	//short right;
};

