#include "AnimatedModel.h"



AnimatedModel::AnimatedModel(vector<ObjModel> models){
	for (int i = 0; i < models.size(); i++)
	{
		objects.push_back(&models[i]);
	}
}

ObjModel AnimatedModel::getModel()
{
	return *objects[index];
}


ObjModel AnimatedModel::firstModel()
{
	if(objects.size() > 0)
	{
		index = 0;
		return *objects[0];
	}
}

ObjModel AnimatedModel::previousModel()
{
	if(index > 0)
	{
		index--;
		return *objects[index];
	}
}

ObjModel AnimatedModel::nextModel()
{
	if(index < objects.size())
	{
		index++;
		return *objects[index];
	}else
	{
		index = 0;
		return *objects[index];
	}
	
}

AnimatedModel::~AnimatedModel()
{
}
