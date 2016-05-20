#pragma once
#include "objmodel.h"
class WarriorModel :
	public ObjModel
{
public:
	WarriorModel(int x, int z);
	~WarriorModel();
	void update() override;
	void InitBoundingSpheres() override;
};

