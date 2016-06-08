#include "AnimatedCollisionModel.h"

AnimatedCollisionModel::AnimatedCollisionModel(vector<CollisionModel *> models)
{
	objects = models;
}

CollisionModel * AnimatedCollisionModel::getModel()
{
	return objects[index];
}

CollisionModel * AnimatedCollisionModel::previousModel()
{
	if (index > 0)
	{
		index--;
		return objects[index];
	}
}

CollisionModel * AnimatedCollisionModel::nextModel()
{
	if (index < objects.size() - 1)
	{
		index++;
		return objects[index];
	}
	else
	{
		index = 0;
		return objects[index];
	}
}

void AnimatedCollisionModel::setIndex(int i)
{
	if (i >= 0 && i < objects.size())
	{
		index = i;
	}
}

AnimatedCollisionModel::~AnimatedCollisionModel()
{
}
