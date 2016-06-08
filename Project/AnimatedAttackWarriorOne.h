#pragma once
#include "WiiHAndler.h"
#include "BowModel.h"
#include "AnimatedCollisionModel.h"

class AnimatedAttackWarriorOne :
	public AnimatedCollisionModel
{
public:
	AnimatedAttackWarriorOne(vector<pair<int, CollisionModel *>> models);
	~AnimatedAttackWarriorOne();

};

