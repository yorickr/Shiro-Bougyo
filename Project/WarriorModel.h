#pragma once

#include "GameState.h"
#include "CollisionModel.h"
#include "Player.h"

enum class WarriorType {first = 0 , second = 1};

class GameState;

class WarriorModel :
	public CollisionModel
{
public:
	WarriorModel(float x, float z, WarriorType type, ObjModel *model, GameState *game);
	~WarriorModel();
	void update(float deltatime) override;
	void InitBoundingSpheres() override;
	void PowerUpBoundingSpheres();
	void setSize(float);
	bool removeHealth(Player* player);//returns true if health <= 0 otherwise false
	void setPosition(int, int, int);
	void setRotation(float, float, float);
private:
	int health = 100;
	WarriorType warriortype;
	short right;
	int isDead;
	GameState *game;
};

