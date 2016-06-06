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
	WarriorModel(float x, float z, WarriorType type, string filename, GameState *game);
	~WarriorModel();
	void update(float deltatime) override;
	void InitBoundingSpheres() override;
	void PowerUpBoundingSpheres();
	void setSize(int);
	bool removeHealth(Player* player);//returns true if health <= 0 otherwise false
	void setPosition(int, int, int);
	void setRotation(int, int, int);
private:
	int health = 100;
	WarriorType warriortype;
	short right;
	int isDead;
	GameState *game;
};

