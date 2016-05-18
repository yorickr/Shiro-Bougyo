#include "BowModel.h"
#include <iostream>
#include "Camera.h"


BowModel::BowModel(Camera * cam): ObjModel("models/bow/Bow_recurve.obj") {
	cout << "Boog aangemaakt";
	cout << "x: " << cam->posX << " y: " << cam->posY;
	camera = cam;
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
