#pragma once
#include "ObjModel.h"
class AnimatedModel 
{
public:
	AnimatedModel(vector<ObjModel*>);
	ObjModel* getModel();
	ObjModel* previousModel();
	ObjModel* nextModel();
	void setIndex(int index);
	~AnimatedModel();

private : 
	vector<ObjModel*> objects;
	int index = 0;

};

