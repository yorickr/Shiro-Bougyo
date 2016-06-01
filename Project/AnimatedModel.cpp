#include "AnimatedModel.h"



AnimatedModel::AnimatedModel(vector<ObjModel*> models){
	objects = models;
}

ObjModel* AnimatedModel::getModel()
{
	return objects[index];
}


void AnimatedModel::setIndex(int i)
{
	if(i >= 0 && i < objects.size())
	{
		index = i;
	}
}

ObjModel* AnimatedModel::previousModel()
{
	if(index > 0)
	{
		index--;
		return objects[index];
	}
}

ObjModel* AnimatedModel::nextModel()
{
	if(index < objects.size() -1)
	{
		index++;
		return objects[index];
	}else
	{
		index = 0;
		return objects[index];
	}
	
}

AnimatedModel::~AnimatedModel()
{
}
