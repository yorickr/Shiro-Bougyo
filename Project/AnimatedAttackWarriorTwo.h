#pragma once
#include "CollisionModel.h"
#include "AnimatedCollisionModel.h"

class AnimatedAttackWarriorTwo :
	public AnimatedCollisionModel
{
public:
	AnimatedAttackWarriorTwo(vector<CollisionModel*> models);
	~AnimatedAttackWarriorTwo();

};

