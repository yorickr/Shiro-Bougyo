#pragma once
#include "objmodel.h"
class WarriorModel :
	public ObjModel
{
public:
	WarriorModel();
	~WarriorModel();
	void update() override;
};

