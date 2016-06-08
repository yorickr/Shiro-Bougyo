#pragma once
#pragma once
#include "CollisionModel.h"
class AnimatedCollisionModel
{
public:
	AnimatedCollisionModel(vector<pair<int, CollisionModel *>> models);
	CollisionModel* getModel();
	CollisionModel* previousModel();
	CollisionModel* nextModel();
	void setIndex(int i);
	~AnimatedCollisionModel();

private:
	vector<pair<int, CollisionModel *>> objects;
	int index = 0;

};
