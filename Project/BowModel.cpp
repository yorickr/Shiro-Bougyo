#include "BowModel.h"
#include <iostream>


BowModel::BowModel(): ObjModel("models/bow/Bow_recurve.obj") {
	
	yrot = -50;
	zpos = 3.5;

}


BowModel::~BowModel()
{
}

void BowModel::draw()
{
	ObjModel::draw();
}

void BowModel::updatepos()
{
	//TODO get CAMERA pos

	//yrot += 0.5;
	
}
