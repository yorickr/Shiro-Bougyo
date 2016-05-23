#pragma once
#include "objmodel.h"
class WarriorModel :
	public ObjModel
{
public:
	WarriorModel(float x, float z);
	~WarriorModel();
	void update() override;
	void InitBoundingSpheres() override;
};

