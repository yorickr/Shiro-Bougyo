#include "WarriorModel.h"



WarriorModel::WarriorModel(int x, int z):ObjModel("models/warrior/warrior.obj")
{
	xpos = x;
	zpos = z;
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
