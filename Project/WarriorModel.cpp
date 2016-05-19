#include "WarriorModel.h"



WarriorModel::WarriorModel():ObjModel("models/warrior/warrior.obj")
{
	xpos = -1;
	zpos = 6;
	ypos -= 1;
}


WarriorModel::~WarriorModel()
{
}

void WarriorModel::update()
{
	//xpos+= 0.1;
	if (xpos > 4)
		xpos = -4;
}
