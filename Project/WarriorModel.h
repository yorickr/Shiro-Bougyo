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
	void PowerUpBoundingSpheres();
	void setSize(int);
	void setPosition(int, int, int);
	bool removeHealth(int health);	//returns true if health <= 0 otherwise false
private:
	int health = 100;
	WarriorType warriortype;
	short right;
};

