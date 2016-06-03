#pragma once

#include "CollisionModel.h"

enum class WarriorType {first, second};

class WarriorModel :
	public CollisionModel
{
public:
	WarriorModel(float x, float z, WarriorType type, string filename);
	~WarriorModel();
	void update(float deltatime) override;
	void InitBoundingSpheres() override;
	void setSize(int);
private:
	WarriorType warriortype;
	short right;
};

