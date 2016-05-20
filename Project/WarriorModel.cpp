#include "WarriorModel.h"



WarriorModel::WarriorModel():ObjModel("models/warrior/warrior.obj")
{
	xpos = -2;
	zpos = 0;
	ypos = -1;
}


WarriorModel::~WarriorModel()
{
}

void WarriorModel::update()
{
	//xpos+= 0.1;
	yrot += 0.5;
}
