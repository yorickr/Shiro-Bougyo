#pragma once

#include "CollisionModel.h"
#include "Player.h"

enum class WarriorType {first = 0 , second = 1};

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
	
	bool removeHealth(Player* player);
	int health = 100;
	//returns true if health <= 0 otherwise false
private:
	
	WarriorType warriortype;
	short right;
};

