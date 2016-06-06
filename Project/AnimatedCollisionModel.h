#pragma once
#pragma once
#include "CollisionModel.h"
class AnimatedCollisionModel
{
public:
	AnimatedCollisionModel(vector<CollisionModel*> models);
	CollisionModel* getModel();
	CollisionModel* previousModel();
	CollisionModel* nextModel();
	void setIndex(int i);
	~AnimatedCollisionModel();

private:
	vector<CollisionModel*> objects;
	int index = 0;

};
