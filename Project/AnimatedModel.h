#pragma once
#include "ObjModel.h"
class AnimatedModel 
{
public:
	AnimatedModel(vector<ObjModel>);
	ObjModel getModel();
	ObjModel firstModel();
	ObjModel previousModel();
	ObjModel nextModel();
	~AnimatedModel();

private : 
	vector<ObjModel*> objects;
	int index = 0;

};

