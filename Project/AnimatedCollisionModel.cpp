#include "AnimatedCollisionModel.h"

AnimatedCollisionModel::AnimatedCollisionModel(vector<pair<int, CollisionModel *>> models)
{
	objects = models;
}

CollisionModel * AnimatedCollisionModel::getModel()
{
	for(int i = 0; i < objects.size(); i++)
	{
		index = i;
		return objects[index].second;
	}
}

CollisionModel * AnimatedCollisionModel::previousModel()
{
	if (index > 0)
	{
		index--;
		for (int i = 0; i < objects.size(); i++)
		{
			index = i;
			return objects[index].second;
		}
	}
}

CollisionModel * AnimatedCollisionModel::nextModel()
{
	if (index < objects.size() - 1)
	{
		index++;
		for (int i = 0; i < objects.size(); i++)
		{
			index = i;
			return objects[index].second;
		}
	}
	else
	{
		index = 0;
		for (int i = 0; i < objects.size(); i++)
		{
			index = i;
			return objects[index].second;
		}
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
