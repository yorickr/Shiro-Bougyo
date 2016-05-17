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
	zpos+= 0.1;
	if (zpos > 10)
		zpos = -10;
}
