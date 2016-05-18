#include "BowModel.h"
#include <iostream>


BowModel::BowModel(): ObjModel("models/bow/Bow_recurve.obj") {
	zpos = -3;
	yrot = 183;
	

}


BowModel::~BowModel()
{
}

void BowModel::draw()
{
	ObjModel::draw();
}

void BowModel::update()
{
	//TODO get CAMERA pos

	//yrot += 0.5;
	
}
