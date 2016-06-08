#pragma once
#include "WiiHAndler.h"
#include "BowModel.h"
#include "AnimatedCollisionModel.h"
#include "WarriorModel.h"

class AnimatedAttackWarriorOne :
	public AnimatedCollisionModel
{
public:
	AnimatedAttackWarriorOne(vector<CollisionModel*> models);
	~AnimatedAttackWarriorOne();

};

