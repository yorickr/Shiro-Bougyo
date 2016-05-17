#include "WarriorModel.h"



WarriorModel::WarriorModel():ObjModel("models/warrior/warrior.obj")
{
	xpos = -1;
	zpos = 2;
	ypos -= 1;
}


WarriorModel::~WarriorModel()
{
}

void WarriorModel::updatepos()
{
	xpos+= 0.1;
	if (xpos > 4)
		xpos = -4;
}